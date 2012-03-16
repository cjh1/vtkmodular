/*=========================================================================

 Program:   Visualization Toolkit
 Module:    vtkAMRBaseReader.cxx

 Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 All rights reserved.
 See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

 =========================================================================*/
#include "vtkAMRBaseReader.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkDataObject.h"
#include "vtkMultiProcessController.h"
#include "vtkOverlappingAMR.h"
#include "vtkDataArraySelection.h"
#include "vtkCallbackCommand.h"
#include "vtkIndent.h"
#include "vtkSmartPointer.h"
#include "vtkCompositeDataPipeline.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkAMRDataSetCache.h"
#include "vtkUniformGrid.h"
#include "vtkDataArray.h"
#include "vtkCellData.h"
#include "vtkPointData.h"
#include "vtkAMRUtilities.h"

#include "vtkTimerLog.h"


#include <cassert>


vtkAMRBaseReader::vtkAMRBaseReader()
{
  this->LoadedMetaData     = false;
  this->NumBlocksFromCache = 0;
  this->NumBlocksFromFile  = 0;
}

//------------------------------------------------------------------------------
vtkAMRBaseReader::~vtkAMRBaseReader()
{
  this->PointDataArraySelection->RemoveObserver( this->SelectionObserver );
  this->CellDataArraySelection->RemoveObserver( this->SelectionObserver );
  this->SelectionObserver->Delete( );
  this->CellDataArraySelection->Delete( );
  this->PointDataArraySelection->Delete( );

  if( this->Cache != NULL )
    {
    this->Cache->Delete();
    }

  if( this->Metadata != NULL )
    {
    this->Metadata->Delete();
    }
}

//------------------------------------------------------------------------------
int vtkAMRBaseReader::FillOutputPortInformation(
    int vtkNotUsed(port),vtkInformation *info )
{
  info->Set( vtkDataObject::DATA_TYPE_NAME(), "vtkOverlappingAMR" );
  return 1;
}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::PrintSelf( std::ostream &os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::Initialize()
{
  vtkTimerLog::MarkStartEvent( "vtkAMRBaseReader::Initialize" );

  this->SetNumberOfInputPorts( 0 );
  this->FileName       = NULL;
  this->MaxLevel       = 0;
  this->Metadata       = NULL;
  this->Controller     = vtkMultiProcessController::GetGlobalController();
  this->InitialRequest = true;
  this->Cache          = vtkAMRDataSetCache::New();

  this->CellDataArraySelection  = vtkDataArraySelection::New();
  this->PointDataArraySelection = vtkDataArraySelection::New();
  this->SelectionObserver       = vtkCallbackCommand::New();
  this->SelectionObserver->SetCallback(
      &vtkAMRBaseReader::SelectionModifiedCallback);
  this->SelectionObserver->SetClientData( this );
  this->CellDataArraySelection->AddObserver(
     vtkCommand::ModifiedEvent,this->SelectionObserver );
  this->PointDataArraySelection->AddObserver(
     vtkCommand::ModifiedEvent, this->SelectionObserver );

  vtkTimerLog::MarkEndEvent( "vtkAMRBaseReader::Initialize" );
}

//----------------------------------------------------------------------------
void vtkAMRBaseReader::SelectionModifiedCallback(
    vtkObject*, unsigned long, void* clientdata, void*)
{
  static_cast<vtkAMRBaseReader*>(clientdata)->Modified();
}

//------------------------------------------------------------------------------
int vtkAMRBaseReader::GetNumberOfPointArrays()
{
  return( this->PointDataArraySelection->GetNumberOfArrays() );
}

//------------------------------------------------------------------------------
int vtkAMRBaseReader::GetNumberOfCellArrays()
{
  return( this->CellDataArraySelection->GetNumberOfArrays() );
}

//------------------------------------------------------------------------------
const char* vtkAMRBaseReader::GetPointArrayName(int index)
{
  return( this->PointDataArraySelection->GetArrayName( index ) );
}

//------------------------------------------------------------------------------
const char* vtkAMRBaseReader::GetCellArrayName(int index)
{
  return( this->CellDataArraySelection->GetArrayName( index )  );
}

//------------------------------------------------------------------------------
int vtkAMRBaseReader::GetPointArrayStatus(const char* name)
{
  return( this->PointDataArraySelection->ArrayIsEnabled( name ) );
}

//------------------------------------------------------------------------------
int vtkAMRBaseReader::GetCellArrayStatus(const char* name)
{
  return( this->CellDataArraySelection->ArrayIsEnabled( name ) );
}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::SetPointArrayStatus(const char* name, int status)
{

  if( status )
    {
    this->PointDataArraySelection->EnableArray(name);
    }
  else
    {
    this->PointDataArraySelection->DisableArray(name);
    }

}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::SetCellArrayStatus(const char* name, int status)
{
  if( status )
    {
    this->CellDataArraySelection->EnableArray( name );
    }
  else
    {
    this->CellDataArraySelection->DisableArray( name );
    }
}

//------------------------------------------------------------------------------
int vtkAMRBaseReader::GetBlockProcessId( const int blockIdx )
{
  // If this is reader instance is serial, return Process 0
  // as the Process ID for the corresponding block.
  if( !this->IsParallel() )
    {
    return 0;
    }

  int N = this->Controller->GetNumberOfProcesses();
  return( blockIdx%N );
}

//------------------------------------------------------------------------------
bool vtkAMRBaseReader::IsBlockMine( const int blockIdx )
{
  // If this reader instance does not run in parallel, then,
  // all blocks are owned by this reader.
  if( !this->IsParallel() )
    {
    return true;
    }

  int myRank = this->Controller->GetLocalProcessId();
  if( myRank == this->GetBlockProcessId( blockIdx ) )
    {
    return true;
    }
  return false;
}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::InitializeArraySelections()
{
  if( this->InitialRequest )
    {
    this->PointDataArraySelection->DisableAllArrays();
    this->CellDataArraySelection->DisableAllArrays();
    this->InitialRequest=false;
    }
}

//------------------------------------------------------------------------------
bool vtkAMRBaseReader::IsParallel( )
{
  if( this->Controller == NULL )
    {
    return false;
    }

  if( this->Controller->GetNumberOfProcesses() > 1 )
    {
    return true;
    }

  return false;
}


//------------------------------------------------------------------------------
int vtkAMRBaseReader::RequestInformation(
    vtkInformation *rqst,
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector )
{
  if( this->LoadedMetaData )
    {
    return( 1 );
    }

  vtkTimerLog::MarkStartEvent( "vtkAMRBaseReader::GenerateMetadata" );
  this->Superclass::RequestInformation( rqst, inputVector, outputVector );
  if( this->Metadata == NULL )
    {
    this->Metadata = vtkOverlappingAMR::New();
    vtkInformation* info = outputVector->GetInformationObject(0);
    assert( "pre: output information object is NULL" && (info != NULL) );
    this->FillMetaData( );
    info->Set( vtkCompositeDataPipeline::COMPOSITE_DATA_META_DATA(),
        this->Metadata );
    }
  vtkTimerLog::MarkStartEvent("vtkAMRBaseReader::GenerateParentChildInformation");
  this->Metadata->GenerateParentChildInformation();
  vtkTimerLog::MarkEndEvent("vtkAMRBaseReader::GenerateParentChildInformation");

  vtkTimerLog::MarkEndEvent( "vtkAMRBaseReader::GenerateMetadata" );

  std::cout << "TOTAL NUMBER OF LEVELS: " << this->Metadata->GetNumberOfLevels()
            << "\n";
  std::cout.flush();
  unsigned int levelIdx = 0;
  for( ; levelIdx < this->Metadata->GetNumberOfLevels(); ++levelIdx )
    {
    std::cout << " \tL(" << levelIdx << ") = "
              << this->Metadata->GetNumberOfDataSets( levelIdx ) << "\n";
    std::cout.flush();
    } // END for levels
  return 1;
}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::SetupBlockRequest( vtkInformation *outInf )
{
  assert( "pre: output information is NULL" && (outInf != NULL) );

  if( outInf->Has(
      vtkCompositeDataPipeline::UPDATE_COMPOSITE_INDICES() ) )
    {
    assert( "Metadata should not be null" && (this->Metadata!=NULL) );
    this->ReadMetaData();

    int size =
     outInf->Length(vtkCompositeDataPipeline::UPDATE_COMPOSITE_INDICES() );
    int *indices =
      outInf->Get(vtkCompositeDataPipeline::UPDATE_COMPOSITE_INDICES() );

    this->BlockMap.clear();
    this->BlockMap.resize( size );

    for( int i=0; i < size; ++i )
      {
      this->BlockMap[ i ] = indices[ i ];
      }
    }
  else
    {
    this->ReadMetaData();
    this->GenerateBlockMap();
    }

}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::GetAMRData(
    const int blockIdx, vtkUniformGrid *block, const char *fieldName )
{
  assert( "pre: AMR block is NULL" && (block != NULL) );
  assert( "pre: field name is NULL" && (fieldName != NULL) );

  // If caching is disabled load the data from file
  if( !this->IsCachingEnabled() )
    {
    vtkTimerLog::MarkStartEvent( "GetAMRGridDataFromFile" );
    this->GetAMRGridData( blockIdx, block, fieldName );
    vtkTimerLog::MarkEndEvent( "GetAMRGridDataFromFile" );
    return;
    }

  // Caching is enabled.
  // Check the cache to see if the data has already been read.
  // Otherwise, read it and cache it.
  if( this->Cache->HasAMRBlockCellData( blockIdx, fieldName ) )
    {
    vtkTimerLog::MarkStartEvent( "GetAMRGridDataFromCache" );
    vtkDataArray *data =
       this->Cache->GetAMRBlockCellData( blockIdx, fieldName );
    assert( "pre: cached data is NULL!" && (data != NULL) );
    vtkTimerLog::MarkEndEvent( "GetAMRGridDataFromCache" );

    block->GetCellData()->AddArray( data );
    }
  else
    {
    vtkTimerLog::MarkStartEvent( "GetAMRGridDataFromFile" );
    this->GetAMRGridData( blockIdx, block, fieldName );
    vtkTimerLog::MarkEndEvent( "GetAMRGridDataFromFile" );

    vtkTimerLog::MarkStartEvent( "CacheAMRData" );
    this->Cache->InsertAMRBlockCellData(
        blockIdx, block->GetCellData()->GetArray( fieldName ) );
    vtkTimerLog::MarkEndEvent( "CacheAMRData" );
    }

}

//------------------------------------------------------------------------------
vtkUniformGrid* vtkAMRBaseReader::GetAMRBlock( const int blockIdx )
{

  // If caching is disabled load the data from file
  if( !this->IsCachingEnabled() )
    {
    ++this->NumBlocksFromFile;
    vtkTimerLog::MarkStartEvent( "ReadAMRBlockFromFile" );
    vtkUniformGrid *gridPtr = this->GetAMRGrid( blockIdx );
    vtkTimerLog::MarkEndEvent( "ReadAMRBlockFromFile" );
    assert( "pre: grid pointer is NULL" && (gridPtr != NULL) );
    return( gridPtr );
    }

  // Caching is enabled.
  // Check the cache to see if the block has already been read.
  // Otherwise, read it and cache it.
  if( this->Cache->HasAMRBlock( blockIdx ) )
    {
    ++this->NumBlocksFromCache;
    vtkTimerLog::MarkStartEvent("ReadAMRBlockFromCache");
    vtkUniformGrid *gridPtr    = vtkUniformGrid::New();
    vtkUniformGrid *cachedGrid = this->Cache->GetAMRBlock( blockIdx );
    gridPtr->CopyStructure( cachedGrid );
    vtkTimerLog::MarkEndEvent( "ReadAMRBlockFromCache" );
    return( gridPtr );
    }
  else
    {
    ++this->NumBlocksFromFile;
    vtkTimerLog::MarkStartEvent( "ReadAMRBlockFromFile" );
    vtkUniformGrid *cachedGrid = vtkUniformGrid::New();
    vtkUniformGrid *gridPtr    = this->GetAMRGrid( blockIdx );
    assert( "pre: grid pointer is NULL" && (gridPtr != NULL) );
    vtkTimerLog::MarkEndEvent( "ReadAMRBlockFromFile" );

    vtkTimerLog::MarkStartEvent( "CacheAMRBlock" );
    cachedGrid->CopyStructure( gridPtr );
    this->Cache->InsertAMRBlock( blockIdx, cachedGrid );
    vtkTimerLog::MarkEndEvent( "CacheAMRBlock" );

    return( gridPtr );
    }

//  assert( "Code should never reach here!" && (false) );
//  return NULL;
}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::LoadPointData(
    const int vtkNotUsed(blockIdx), vtkUniformGrid* vtkNotUsed(block) )
{
  // TODO: implement this
  //vtkErrorMacro( "Node-centered AMR data are not currently supported" );
}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::LoadCellData(
    const int blockIdx, vtkUniformGrid *block )
{
  // Sanity check!
  assert( "pre: AMR block should not be NULL" && (block != NULL) );

  for( int i=0; i < this->GetNumberOfCellArrays(); ++i )
    {
    if( this->GetCellArrayStatus( this->GetCellArrayName( i ) ) )
      {
      this->GetAMRData( blockIdx, block, this->GetCellArrayName( i ) );
      }
    } // END for all cell arrays
}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::LoadRequestedBlocks( vtkOverlappingAMR *output )
{
  assert( "pre: AMR data-structure is NULL" && (output != NULL) );

  //STEP 1: Gather all blocks loaded by each process
  int numBlocks = static_cast< int >( this->BlockMap.size() );
  for( int block=0; block < numBlocks; ++block )
    {
    int blockIdx = this->BlockMap[ block ];
    int level    = this->GetBlockLevel( blockIdx );

     // STEP 0: Get the AMR block
    vtkTimerLog::MarkStartEvent( "GetAMRBlock" );
    vtkUniformGrid *amrBlock = this->GetAMRBlock( blockIdx );
    vtkTimerLog::MarkEndEvent( "GetAMRBlock" );
    assert( "pre: AMR block is NULL" && (amrBlock != NULL) );

    // STEP 2: Load any point-data
    vtkTimerLog::MarkStartEvent( "vtkARMBaseReader::LoadPointData" );
    this->LoadPointData( blockIdx, amrBlock );
    vtkTimerLog::MarkEndEvent( "vtkAMRBaseReader::LoadPointData" );

    // STEP 3: Load any cell data
    vtkTimerLog::MarkStartEvent( "vtkAMRBaseReader::LoadCellData" );
    this->LoadCellData( blockIdx, amrBlock );
    vtkTimerLog::MarkEndEvent( "vtkAMRBaseReader::LoadCellData" );

    // STEP 4: Add dataset
    unsigned int metaLevel = 0;
    unsigned int metaIdx   = 0;
    this->Metadata->GetLevelAndIndex( blockIdx, metaLevel, metaIdx );

    output->SetDataSet( level,metaIdx,amrBlock );
    amrBlock->Delete();
    } // END for all blocks

  assert( "pre: Metadata should not be NULL" && (this->Metadata != NULL) );
  assert( "pre: NumLevels in output should be <= to NumLevels in metadata" &&
           output->GetNumberOfLevels() <= this->Metadata->GetNumberOfLevels() );

#ifndef NDEBUG
  unsigned int levelIdx = 0;
  for( ; levelIdx < output->GetNumberOfLevels(); ++levelIdx )
    {
    unsigned int N         = output->GetNumberOfDataSets( levelIdx );
    unsigned int Nexpected = this->Metadata->GetNumberOfDataSets( levelIdx );
    assert( "pre: NumData at level must correspond to the metadata" &&
        N <= Nexpected );
    }
#endif

}

//------------------------------------------------------------------------------
void vtkAMRBaseReader::AssignAndLoadBlocks( vtkOverlappingAMR *output )
{
  assert( "pre: AMR data-structure is NULL" && (output != NULL) );

  // Initialize counter of the number of blocks at each level.
  // This counter is used to compute the block index w.r.t. the
  // hierarchical box data-structure. Note that then number of blocks
  // can change based on user constraints, e.g., the number of levels
  // visible.
  std::vector< int > idxcounter;
  idxcounter.resize(this->GetNumberOfLevels()+1, 0);

  // Find the number of blocks to be processed. BlockMap.size()
  // has all the blocks that are to be processesed and may be
  // less than or equal to this->GetNumberOfBlocks(), i.e., the
  // total number of blocks.
  int numBlocks = static_cast< int >( this->BlockMap.size() );
  for( int block=0; block < numBlocks; ++block )
    {
    int blockIdx = this->BlockMap[ block ];
    int level    = this->GetBlockLevel( blockIdx );

    if( this->IsBlockMine(block) )
      {
      // STEP 0: Get the AMR block
      vtkTimerLog::MarkStartEvent( "GetAMRBlock" );
      vtkUniformGrid *amrBlock = this->GetAMRBlock( blockIdx );
      vtkTimerLog::MarkEndEvent( "GetAMRBlock" );
      assert( "pre: AMR block is NULL" && (amrBlock != NULL) );

      // STEP 2: Load any point-data
      vtkTimerLog::MarkStartEvent( "vtkARMBaseReader::LoadPointData" );
      this->LoadPointData( blockIdx, amrBlock );
      vtkTimerLog::MarkEndEvent( "vtkAMRBaseReader::LoadPointData" );

      // STEP 3: Load any cell data
      vtkTimerLog::MarkStartEvent( "vtkAMRBaseReader::LoadCellData" );
      this->LoadCellData( blockIdx, amrBlock );
      vtkTimerLog::MarkEndEvent( "vtkAMRBaseReader::LoadCellData" );

      // STEP 4: Add dataset
      output->SetDataSet( level,idxcounter[level],amrBlock );
      amrBlock->Delete();
      idxcounter[level]++;
      } // END if the block belongs to this process
    else
      {
      output->SetDataSet( level, idxcounter[level], NULL );
      idxcounter[level]++;
      }
    } // END for all blocks
}

//------------------------------------------------------------------------------
int vtkAMRBaseReader::RequestData(
        vtkInformation* vtkNotUsed(request),
        vtkInformationVector** vtkNotUsed(inputVector),
        vtkInformationVector* outputVector )
{
  vtkTimerLog::MarkStartEvent( "vtkAMRBaseReader::RqstData" );
  this->NumBlocksFromCache = 0;
  this->NumBlocksFromFile  = 0;

  vtkInformation    *outInf = outputVector->GetInformationObject( 0 );
  vtkOverlappingAMR *output =
    vtkOverlappingAMR::SafeDownCast(
     outInf->Get( vtkDataObject::DATA_OBJECT() ) );
  assert( "pre: output AMR dataset is NULL" && ( output != NULL ) );

  // Setup the block request
  vtkTimerLog::MarkStartEvent( "vtkAMRBaseReader::SetupBlockRequest" );
  this->SetupBlockRequest( outInf );
  vtkTimerLog::MarkEndEvent( "vtkAMRBaseReader::SetupBlockRequest" );

  if( outInf->Has( vtkCompositeDataPipeline::LOAD_REQUESTED_BLOCKS() ) )
    {
    this->LoadRequestedBlocks( output );
    }
  else
    {
    this->AssignAndLoadBlocks( output );

    // Generate all the AMR metadata & the visibility arrays
    vtkTimerLog::MarkStartEvent( "AMRUtilities::GenerateMetaData" );
    vtkAMRUtilities::GenerateMetaData( output, this->Controller );
    vtkTimerLog::MarkEndEvent( "AMRUtilities::GenerateMetaData" );

    //If there is a downstream module, do not generate visibility arrays here.
    if(!outInf->Has( vtkCompositeDataPipeline::UPDATE_COMPOSITE_INDICES() ) )
      {
      vtkTimerLog::MarkStartEvent( "AMR::GenerateVisibilityArrays" );
      output->GenerateVisibilityArrays();
      vtkTimerLog::MarkEndEvent( "AMR::GenerateVisibilityArrays" );
      }
    }

  // If this instance of the reader is not parallel, block until all processes
  // read their blocks.
  if( this->IsParallel() )
    {
    this->Controller->Barrier();
    }

  outInf = NULL;
  output = NULL;

  vtkTimerLog::MarkEndEvent( "vtkAMRBaseReader::RqstData" );

  return 1;
}
