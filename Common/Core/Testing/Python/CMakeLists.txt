if (VTK_PYTHON_EXE)
  foreach ( tfile
      PythonSmoke
      TestArrayArguments
      TestExecuteMethodFinalizeCrash
      TestGhost
      TestIgnoreBTX
      TestMutable
      TestNumpySupport
      TestOperators
      TestStrings
      TestSubClass
      TestTemplates
      TestTerminationCrash
      TestVariant
      TestWeakref
      )
    add_test(${tfile}Python ${VTK_PYTHON_EXE}
      ${VTK_SOURCE_DIR}/Common/Core/Testing/Python/${tfile}.py)
  endforeach()
  if (VTK_USE_N_WAY_ARRAYS)
    foreach ( tfile
      TestStrings
      TestVariant
      TestOperators
      )
      add_test(${tfile}Python ${VTK_PYTHON_EXE}
        ${VTK_SOURCE_DIR}/Common/Core/Python/${tfile}.py)
    endforeach()
  endif()
endif()
