/*=========================================================================

  Program:   Visualization Toolkit
  Module:    TestHandleWidget3D.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This example tests the vtkFixedSizeHandleRepresentation3D class. This
// is a 3D handle that maintains a fixed size in display space. This is
// useful when placing markers on datasets. The size in pixels may be set via
// SetHandleSizeInPixels. This representation renders the markers as spherical
// blobs in 3D space with the width as specified above, defaults to 10 pixels.
// The handles will have the same size in pixels, give or take a certain
// tolerance, as specified by SetHandleSizeToleranceInPixels. The tolerance
// defaults to half a pixel. PointPlacers may be used to specify constraints on
// the placement of markers. For instance a vtkPolygonalSurfacePointPlacer
// will constrain placement of these spherical handles to a surface mesh.

#include "vtkSmartPointer.h"
#include "vtkFixedSizeHandleRepresentation3D.h"
#include "vtkHandleWidget.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCommand.h"
#include "vtkSphereSource.h"
#include "vtkPolyData.h"
#include "vtkTestUtilities.h"
#include "vtkTesting.h"

char TestFixedSizeHandleRepresentation3DLog[] =
"# StreamVersion 1\n"
"RenderEvent 0 0 0 0 0 0 0\n"
"EnterEvent 156 11 0 0 0 0 0\n"
"MouseMoveEvent 156 11 0 0 0 0 0\n"
"MouseMoveEvent 158 25 0 0 0 0 0\n"
"MouseMoveEvent 159 39 0 0 0 0 0\n"
"MouseMoveEvent 163 55 0 0 0 0 0\n"
"MouseMoveEvent 164 68 0 0 0 0 0\n"
"MouseMoveEvent 166 81 0 0 0 0 0\n"
"MouseMoveEvent 167 91 0 0 0 0 0\n"
"MouseMoveEvent 169 99 0 0 0 0 0\n"
"MouseMoveEvent 170 106 0 0 0 0 0\n"
"MouseMoveEvent 170 111 0 0 0 0 0\n"
"MouseMoveEvent 170 115 0 0 0 0 0\n"
"MouseMoveEvent 171 118 0 0 0 0 0\n"
"MouseMoveEvent 171 121 0 0 0 0 0\n"
"MouseMoveEvent 171 123 0 0 0 0 0\n"
"MouseMoveEvent 171 124 0 0 0 0 0\n"
"MouseMoveEvent 171 127 0 0 0 0 0\n"
"MouseMoveEvent 171 129 0 0 0 0 0\n"
"MouseMoveEvent 171 131 0 0 0 0 0\n"
"MouseMoveEvent 171 133 0 0 0 0 0\n"
"MouseMoveEvent 171 135 0 0 0 0 0\n"
"MouseMoveEvent 171 136 0 0 0 0 0\n"
"MouseMoveEvent 171 137 0 0 0 0 0\n"
"MouseMoveEvent 171 139 0 0 0 0 0\n"
"MouseMoveEvent 171 140 0 0 0 0 0\n"
"MouseMoveEvent 171 141 0 0 0 0 0\n"
"MouseMoveEvent 171 142 0 0 0 0 0\n"
"MouseMoveEvent 170 144 0 0 0 0 0\n"
"MouseMoveEvent 169 145 0 0 0 0 0\n"
"MouseMoveEvent 169 146 0 0 0 0 0\n"
"MouseMoveEvent 168 146 0 0 0 0 0\n"
"MouseMoveEvent 168 147 0 0 0 0 0\n"
"MouseMoveEvent 167 147 0 0 0 0 0\n"
"MouseMoveEvent 166 148 0 0 0 0 0\n"
"MouseMoveEvent 166 149 0 0 0 0 0\n"
"MouseMoveEvent 165 149 0 0 0 0 0\n"
"MouseMoveEvent 164 149 0 0 0 0 0\n"
"MouseMoveEvent 163 149 0 0 0 0 0\n"
"MouseMoveEvent 162 149 0 0 0 0 0\n"
"MouseMoveEvent 161 149 0 0 0 0 0\n"
"MouseMoveEvent 160 148 0 0 0 0 0\n"
"MouseMoveEvent 159 148 0 0 0 0 0\n"
"MouseMoveEvent 159 147 0 0 0 0 0\n"
"MouseMoveEvent 158 147 0 0 0 0 0\n"
"MouseMoveEvent 157 146 0 0 0 0 0\n"
"MouseMoveEvent 156 146 0 0 0 0 0\n"
"MouseMoveEvent 156 145 0 0 0 0 0\n"
"MouseMoveEvent 155 145 0 0 0 0 0\n"
"MouseMoveEvent 154 145 0 0 0 0 0\n"
"MouseMoveEvent 153 145 0 0 0 0 0\n"
"MouseMoveEvent 152 145 0 0 0 0 0\n"
"MouseMoveEvent 151 145 0 0 0 0 0\n"
"MouseMoveEvent 150 145 0 0 0 0 0\n"
"LeftButtonPressEvent 150 145 0 0 0 0 0\n"
"RenderEvent 150 145 0 0 0 0 0\n"
"MouseMoveEvent 150 144 0 0 0 0 0\n"
"RenderEvent 150 144 0 0 0 0 0\n"
"MouseMoveEvent 150 141 0 0 0 0 0\n"
"RenderEvent 150 141 0 0 0 0 0\n"
"MouseMoveEvent 150 138 0 0 0 0 0\n"
"RenderEvent 150 138 0 0 0 0 0\n"
"MouseMoveEvent 150 133 0 0 0 0 0\n"
"RenderEvent 150 133 0 0 0 0 0\n"
"MouseMoveEvent 150 130 0 0 0 0 0\n"
"RenderEvent 150 130 0 0 0 0 0\n"
"MouseMoveEvent 150 127 0 0 0 0 0\n"
"RenderEvent 150 127 0 0 0 0 0\n"
"MouseMoveEvent 150 125 0 0 0 0 0\n"
"RenderEvent 150 125 0 0 0 0 0\n"
"MouseMoveEvent 150 123 0 0 0 0 0\n"
"RenderEvent 150 123 0 0 0 0 0\n"
"MouseMoveEvent 150 122 0 0 0 0 0\n"
"RenderEvent 150 122 0 0 0 0 0\n"
"MouseMoveEvent 150 121 0 0 0 0 0\n"
"RenderEvent 150 121 0 0 0 0 0\n"
"LeftButtonReleaseEvent 150 121 0 0 0 0 0\n"
"RenderEvent 150 121 0 0 0 0 0\n"
"MouseMoveEvent 150 121 0 0 0 0 0\n"
"KeyPressEvent 150 121 0 0 116 1 t\n"
"CharEvent 150 121 0 0 116 1 t\n"
"KeyReleaseEvent 150 121 0 0 116 1 t\n"
"MouseMoveEvent 152 119 0 0 0 0 t\n"
"MouseMoveEvent 153 117 0 0 0 0 t\n"
"MouseMoveEvent 154 115 0 0 0 0 t\n"
"MouseMoveEvent 156 114 0 0 0 0 t\n"
"MouseMoveEvent 157 112 0 0 0 0 t\n"
"MouseMoveEvent 158 112 0 0 0 0 t\n"
"MouseMoveEvent 158 111 0 0 0 0 t\n"
"MouseMoveEvent 158 111 0 0 0 0 t\n"
"MouseMoveEvent 158 111 0 0 0 0 t\n"
"MouseMoveEvent 158 111 0 0 0 0 t\n"
"RightButtonPressEvent 158 111 0 0 0 0 t\n"
"StartInteractionEvent 158 111 0 0 0 0 t\n"
"MouseMoveEvent 158 112 0 0 0 0 t\n"
"RenderEvent 158 112 0 0 0 0 t\n"
"MouseMoveEvent 156 115 0 0 0 0 t\n"
"RenderEvent 156 115 0 0 0 0 t\n"
"MouseMoveEvent 155 118 0 0 0 0 t\n"
"RenderEvent 155 118 0 0 0 0 t\n"
"MouseMoveEvent 153 124 0 0 0 0 t\n"
"RenderEvent 153 124 0 0 0 0 t\n"
"MouseMoveEvent 153 128 0 0 0 0 t\n"
"RenderEvent 153 128 0 0 0 0 t\n"
"MouseMoveEvent 150 135 0 0 0 0 t\n"
"RenderEvent 150 135 0 0 0 0 t\n"
"MouseMoveEvent 148 142 0 0 0 0 t\n"
"RenderEvent 148 142 0 0 0 0 t\n"
"MouseMoveEvent 148 149 0 0 0 0 t\n"
"RenderEvent 148 149 0 0 0 0 t\n"
"MouseMoveEvent 146 157 0 0 0 0 t\n"
"RenderEvent 146 157 0 0 0 0 t\n"
"MouseMoveEvent 145 165 0 0 0 0 t\n"
"RenderEvent 145 165 0 0 0 0 t\n"
"MouseMoveEvent 145 172 0 0 0 0 t\n"
"RenderEvent 145 172 0 0 0 0 t\n"
"MouseMoveEvent 145 179 0 0 0 0 t\n"
"RenderEvent 145 179 0 0 0 0 t\n"
"MouseMoveEvent 145 185 0 0 0 0 t\n"
"RenderEvent 145 185 0 0 0 0 t\n"
"MouseMoveEvent 145 191 0 0 0 0 t\n"
"RenderEvent 145 191 0 0 0 0 t\n"
"MouseMoveEvent 145 197 0 0 0 0 t\n"
"RenderEvent 145 197 0 0 0 0 t\n"
"MouseMoveEvent 144 201 0 0 0 0 t\n"
"RenderEvent 144 201 0 0 0 0 t\n"
"MouseMoveEvent 144 203 0 0 0 0 t\n"
"RenderEvent 144 203 0 0 0 0 t\n"
"MouseMoveEvent 144 205 0 0 0 0 t\n"
"RenderEvent 144 205 0 0 0 0 t\n"
"MouseMoveEvent 144 206 0 0 0 0 t\n"
"RenderEvent 144 206 0 0 0 0 t\n"
"MouseMoveEvent 144 208 0 0 0 0 t\n"
"RenderEvent 144 208 0 0 0 0 t\n"
"MouseMoveEvent 144 209 0 0 0 0 t\n"
"RenderEvent 144 209 0 0 0 0 t\n"
"MouseMoveEvent 144 212 0 0 0 0 t\n"
"RenderEvent 144 212 0 0 0 0 t\n"
"MouseMoveEvent 144 213 0 0 0 0 t\n"
"RenderEvent 144 213 0 0 0 0 t\n"
"MouseMoveEvent 144 214 0 0 0 0 t\n"
"RenderEvent 144 214 0 0 0 0 t\n"
"MouseMoveEvent 144 215 0 0 0 0 t\n"
"RenderEvent 144 215 0 0 0 0 t\n"
"MouseMoveEvent 144 216 0 0 0 0 t\n"
"RenderEvent 144 216 0 0 0 0 t\n"
"MouseMoveEvent 144 217 0 0 0 0 t\n"
"RenderEvent 144 217 0 0 0 0 t\n"
"MouseMoveEvent 144 218 0 0 0 0 t\n"
"RenderEvent 144 218 0 0 0 0 t\n"
"MouseMoveEvent 144 219 0 0 0 0 t\n"
"RenderEvent 144 219 0 0 0 0 t\n"
"RightButtonReleaseEvent 144 219 0 0 0 0 t\n"
"EndInteractionEvent 144 219 0 0 0 0 t\n"
"RenderEvent 144 219 0 0 0 0 t\n"
"MouseMoveEvent 144 219 0 0 0 0 t\n"
"MouseMoveEvent 144 211 0 0 0 0 t\n"
"MouseMoveEvent 145 199 0 0 0 0 t\n"
"MouseMoveEvent 146 187 0 0 0 0 t\n"
"MouseMoveEvent 146 174 0 0 0 0 t\n"
"MouseMoveEvent 147 162 0 0 0 0 t\n"
"MouseMoveEvent 148 151 0 0 0 0 t\n"
"MouseMoveEvent 148 142 0 0 0 0 t\n"
"MouseMoveEvent 148 133 0 0 0 0 t\n"
"MouseMoveEvent 148 126 0 0 0 0 t\n"
"MouseMoveEvent 148 120 0 0 0 0 t\n"
"MouseMoveEvent 148 116 0 0 0 0 t\n"
"MouseMoveEvent 148 113 0 0 0 0 t\n"
"MouseMoveEvent 148 112 0 0 0 0 t\n"
"MouseMoveEvent 148 111 0 0 0 0 t\n"
"MouseMoveEvent 148 110 0 0 0 0 t\n"
"MouseMoveEvent 148 109 0 0 0 0 t\n"
"MouseMoveEvent 148 108 0 0 0 0 t\n"
"MouseMoveEvent 147 107 0 0 0 0 t\n"
"MouseMoveEvent 147 105 0 0 0 0 t\n"
"MouseMoveEvent 147 104 0 0 0 0 t\n"
"MouseMoveEvent 147 103 0 0 0 0 t\n"
"MouseMoveEvent 146 101 0 0 0 0 t\n"
"MouseMoveEvent 146 99 0 0 0 0 t\n"
"MouseMoveEvent 146 98 0 0 0 0 t\n"
"MouseMoveEvent 146 97 0 0 0 0 t\n"
"MouseMoveEvent 146 96 0 0 0 0 t\n"
"MouseMoveEvent 147 96 0 0 0 0 t\n"
"MouseMoveEvent 148 96 0 0 0 0 t\n"
"LeftButtonPressEvent 148 96 0 0 0 0 t\n"
"RenderEvent 148 96 0 0 0 0 t\n"
"MouseMoveEvent 148 97 0 0 0 0 t\n"
"RenderEvent 148 97 0 0 0 0 t\n"
"MouseMoveEvent 148 98 0 0 0 0 t\n"
"RenderEvent 148 98 0 0 0 0 t\n"
"MouseMoveEvent 148 103 0 0 0 0 t\n"
"RenderEvent 148 103 0 0 0 0 t\n"
"MouseMoveEvent 148 107 0 0 0 0 t\n"
"RenderEvent 148 107 0 0 0 0 t\n"
"MouseMoveEvent 147 114 0 0 0 0 t\n"
"RenderEvent 147 114 0 0 0 0 t\n"
"MouseMoveEvent 146 120 0 0 0 0 t\n"
"RenderEvent 146 120 0 0 0 0 t\n"
"MouseMoveEvent 145 124 0 0 0 0 t\n"
"RenderEvent 145 124 0 0 0 0 t\n"
"MouseMoveEvent 145 128 0 0 0 0 t\n"
"RenderEvent 145 128 0 0 0 0 t\n"
"MouseMoveEvent 145 133 0 0 0 0 t\n"
"RenderEvent 145 133 0 0 0 0 t\n"
"MouseMoveEvent 144 136 0 0 0 0 t\n"
"RenderEvent 144 136 0 0 0 0 t\n"
"MouseMoveEvent 144 140 0 0 0 0 t\n"
"RenderEvent 144 140 0 0 0 0 t\n"
"MouseMoveEvent 144 144 0 0 0 0 t\n"
"RenderEvent 144 144 0 0 0 0 t\n"
"MouseMoveEvent 144 147 0 0 0 0 t\n"
"RenderEvent 144 147 0 0 0 0 t\n"
"MouseMoveEvent 144 151 0 0 0 0 t\n"
"RenderEvent 144 151 0 0 0 0 t\n"
"MouseMoveEvent 143 155 0 0 0 0 t\n"
"RenderEvent 143 155 0 0 0 0 t\n"
"MouseMoveEvent 143 158 0 0 0 0 t\n"
"RenderEvent 143 158 0 0 0 0 t\n"
"MouseMoveEvent 142 160 0 0 0 0 t\n"
"RenderEvent 142 160 0 0 0 0 t\n"
"MouseMoveEvent 142 162 0 0 0 0 t\n"
"RenderEvent 142 162 0 0 0 0 t\n"
"MouseMoveEvent 142 164 0 0 0 0 t\n"
"RenderEvent 142 164 0 0 0 0 t\n"
"MouseMoveEvent 142 165 0 0 0 0 t\n"
"RenderEvent 142 165 0 0 0 0 t\n"
"MouseMoveEvent 141 166 0 0 0 0 t\n"
"RenderEvent 141 166 0 0 0 0 t\n"
"MouseMoveEvent 140 168 0 0 0 0 t\n"
"RenderEvent 140 168 0 0 0 0 t\n"
"MouseMoveEvent 140 169 0 0 0 0 t\n"
"RenderEvent 140 169 0 0 0 0 t\n"
"MouseMoveEvent 140 170 0 0 0 0 t\n"
"RenderEvent 140 170 0 0 0 0 t\n"
"MouseMoveEvent 140 169 0 0 0 0 t\n"
"RenderEvent 140 169 0 0 0 0 t\n"
"LeftButtonReleaseEvent 140 169 0 0 0 0 t\n"
"RenderEvent 140 169 0 0 0 0 t\n"
"MouseMoveEvent 140 169 0 0 0 0 t\n"
"MouseMoveEvent 145 174 0 0 0 0 t\n"
"MouseMoveEvent 151 179 0 0 0 0 t\n"
"MouseMoveEvent 157 183 0 0 0 0 t\n"
"MouseMoveEvent 161 186 0 0 0 0 t\n"
"MouseMoveEvent 164 189 0 0 0 0 t\n"
"MouseMoveEvent 166 190 0 0 0 0 t\n"
"MouseMoveEvent 166 191 0 0 0 0 t\n"
"MouseMoveEvent 167 192 0 0 0 0 t\n"
"MouseMoveEvent 167 193 0 0 0 0 t\n"
"MouseMoveEvent 169 196 0 0 0 0 t\n"
"MouseMoveEvent 172 199 0 0 0 0 t\n"
"MouseMoveEvent 175 203 0 0 0 0 t\n"
"MouseMoveEvent 178 207 0 0 0 0 t\n"
"MouseMoveEvent 182 211 0 0 0 0 t\n"
"MouseMoveEvent 183 213 0 0 0 0 t\n"
"MouseMoveEvent 184 214 0 0 0 0 t\n"
"MouseMoveEvent 184 216 0 0 0 0 t\n"
"RightButtonPressEvent 184 216 0 0 0 0 t\n"
"StartInteractionEvent 184 216 0 0 0 0 t\n"
"MouseMoveEvent 183 216 0 0 0 0 t\n"
"RenderEvent 183 216 0 0 0 0 t\n"
"MouseMoveEvent 182 215 0 0 0 0 t\n"
"RenderEvent 182 215 0 0 0 0 t\n"
"MouseMoveEvent 181 213 0 0 0 0 t\n"
"RenderEvent 181 213 0 0 0 0 t\n"
"MouseMoveEvent 181 212 0 0 0 0 t\n"
"RenderEvent 181 212 0 0 0 0 t\n"
"MouseMoveEvent 180 208 0 0 0 0 t\n"
"RenderEvent 180 208 0 0 0 0 t\n"
"MouseMoveEvent 179 204 0 0 0 0 t\n"
"RenderEvent 179 204 0 0 0 0 t\n"
"MouseMoveEvent 178 200 0 0 0 0 t\n"
"RenderEvent 178 200 0 0 0 0 t\n"
"MouseMoveEvent 177 195 0 0 0 0 t\n"
"RenderEvent 177 195 0 0 0 0 t\n"
"MouseMoveEvent 177 191 0 0 0 0 t\n"
"RenderEvent 177 191 0 0 0 0 t\n"
"MouseMoveEvent 176 187 0 0 0 0 t\n"
"RenderEvent 176 187 0 0 0 0 t\n"
"MouseMoveEvent 175 183 0 0 0 0 t\n"
"RenderEvent 175 183 0 0 0 0 t\n"
"MouseMoveEvent 174 180 0 0 0 0 t\n"
"RenderEvent 174 180 0 0 0 0 t\n"
"MouseMoveEvent 174 177 0 0 0 0 t\n"
"RenderEvent 174 177 0 0 0 0 t\n"
"MouseMoveEvent 174 174 0 0 0 0 t\n"
"RenderEvent 174 174 0 0 0 0 t\n"
"MouseMoveEvent 173 171 0 0 0 0 t\n"
"RenderEvent 173 171 0 0 0 0 t\n"
"MouseMoveEvent 173 167 0 0 0 0 t\n"
"RenderEvent 173 167 0 0 0 0 t\n"
"MouseMoveEvent 173 164 0 0 0 0 t\n"
"RenderEvent 173 164 0 0 0 0 t\n"
"MouseMoveEvent 173 161 0 0 0 0 t\n"
"RenderEvent 173 161 0 0 0 0 t\n"
"MouseMoveEvent 172 157 0 0 0 0 t\n"
"RenderEvent 172 157 0 0 0 0 t\n"
"MouseMoveEvent 172 155 0 0 0 0 t\n"
"RenderEvent 172 155 0 0 0 0 t\n"
"MouseMoveEvent 172 151 0 0 0 0 t\n"
"RenderEvent 172 151 0 0 0 0 t\n"
"MouseMoveEvent 172 147 0 0 0 0 t\n"
"RenderEvent 172 147 0 0 0 0 t\n"
"MouseMoveEvent 171 143 0 0 0 0 t\n"
"RenderEvent 171 143 0 0 0 0 t\n"
"MouseMoveEvent 171 137 0 0 0 0 t\n"
"RenderEvent 171 137 0 0 0 0 t\n"
"MouseMoveEvent 171 133 0 0 0 0 t\n"
"RenderEvent 171 133 0 0 0 0 t\n"
"MouseMoveEvent 171 129 0 0 0 0 t\n"
"RenderEvent 171 129 0 0 0 0 t\n"
"MouseMoveEvent 171 125 0 0 0 0 t\n"
"RenderEvent 171 125 0 0 0 0 t\n"
"MouseMoveEvent 171 121 0 0 0 0 t\n"
"RenderEvent 171 121 0 0 0 0 t\n"
"MouseMoveEvent 171 115 0 0 0 0 t\n"
"RenderEvent 171 115 0 0 0 0 t\n"
"MouseMoveEvent 171 111 0 0 0 0 t\n"
"RenderEvent 171 111 0 0 0 0 t\n"
"MouseMoveEvent 171 106 0 0 0 0 t\n"
"RenderEvent 171 106 0 0 0 0 t\n"
"MouseMoveEvent 171 100 0 0 0 0 t\n"
"RenderEvent 171 100 0 0 0 0 t\n"
"MouseMoveEvent 171 94 0 0 0 0 t\n"
"RenderEvent 171 94 0 0 0 0 t\n"
"MouseMoveEvent 171 86 0 0 0 0 t\n"
"RenderEvent 171 86 0 0 0 0 t\n"
"MouseMoveEvent 171 79 0 0 0 0 t\n"
"RenderEvent 171 79 0 0 0 0 t\n"
"MouseMoveEvent 171 72 0 0 0 0 t\n"
"RenderEvent 171 72 0 0 0 0 t\n"
"MouseMoveEvent 171 65 0 0 0 0 t\n"
"RenderEvent 171 65 0 0 0 0 t\n"
"MouseMoveEvent 171 60 0 0 0 0 t\n"
"RenderEvent 171 60 0 0 0 0 t\n"
"MouseMoveEvent 171 56 0 0 0 0 t\n"
"RenderEvent 171 56 0 0 0 0 t\n"
"MouseMoveEvent 171 52 0 0 0 0 t\n"
"RenderEvent 171 52 0 0 0 0 t\n"
"MouseMoveEvent 171 48 0 0 0 0 t\n"
"RenderEvent 171 48 0 0 0 0 t\n"
"MouseMoveEvent 171 42 0 0 0 0 t\n"
"RenderEvent 171 42 0 0 0 0 t\n"
"MouseMoveEvent 171 37 0 0 0 0 t\n"
"RenderEvent 171 37 0 0 0 0 t\n"
"MouseMoveEvent 171 31 0 0 0 0 t\n"
"RenderEvent 171 31 0 0 0 0 t\n"
"MouseMoveEvent 171 27 0 0 0 0 t\n"
"RenderEvent 171 27 0 0 0 0 t\n"
"MouseMoveEvent 171 23 0 0 0 0 t\n"
"RenderEvent 171 23 0 0 0 0 t\n"
"MouseMoveEvent 171 20 0 0 0 0 t\n"
"RenderEvent 171 20 0 0 0 0 t\n"
"MouseMoveEvent 171 19 0 0 0 0 t\n"
"RenderEvent 171 19 0 0 0 0 t\n"
"MouseMoveEvent 172 16 0 0 0 0 t\n"
"RenderEvent 172 16 0 0 0 0 t\n"
"MouseMoveEvent 172 14 0 0 0 0 t\n"
"RenderEvent 172 14 0 0 0 0 t\n"
"MouseMoveEvent 173 12 0 0 0 0 t\n"
"RenderEvent 173 12 0 0 0 0 t\n"
"MouseMoveEvent 173 11 0 0 0 0 t\n"
"RenderEvent 173 11 0 0 0 0 t\n"
"MouseMoveEvent 173 10 0 0 0 0 t\n"
"RenderEvent 173 10 0 0 0 0 t\n"
"MouseMoveEvent 173 9 0 0 0 0 t\n"
"RenderEvent 173 9 0 0 0 0 t\n"
"MouseMoveEvent 173 8 0 0 0 0 t\n"
"RenderEvent 173 8 0 0 0 0 t\n"
"MouseMoveEvent 173 5 0 0 0 0 t\n"
"RenderEvent 173 5 0 0 0 0 t\n"
"MouseMoveEvent 173 0 0 0 0 0 t\n"
"RenderEvent 173 0 0 0 0 0 t\n"
"MouseMoveEvent 173 -4 0 0 0 0 t\n"
"RenderEvent 173 -4 0 0 0 0 t\n"
"MouseMoveEvent 173 -9 0 0 0 0 t\n"
"RenderEvent 173 -9 0 0 0 0 t\n"
"MouseMoveEvent 173 -11 0 0 0 0 t\n"
"RenderEvent 173 -11 0 0 0 0 t\n"
"MouseMoveEvent 173 -13 0 0 0 0 t\n"
"RenderEvent 173 -13 0 0 0 0 t\n"
"MouseMoveEvent 173 -14 0 0 0 0 t\n"
"RenderEvent 173 -14 0 0 0 0 t\n"
"MouseMoveEvent 173 -15 0 0 0 0 t\n"
"RenderEvent 173 -15 0 0 0 0 t\n"
"MouseMoveEvent 173 -16 0 0 0 0 t\n"
"RenderEvent 173 -16 0 0 0 0 t\n"
"MouseMoveEvent 173 -18 0 0 0 0 t\n"
"RenderEvent 173 -18 0 0 0 0 t\n"
"MouseMoveEvent 173 -19 0 0 0 0 t\n"
"RenderEvent 173 -19 0 0 0 0 t\n"
"MouseMoveEvent 173 -21 0 0 0 0 t\n"
"RenderEvent 173 -21 0 0 0 0 t\n"
"MouseMoveEvent 173 -23 0 0 0 0 t\n"
"RenderEvent 173 -23 0 0 0 0 t\n"
"MouseMoveEvent 173 -26 0 0 0 0 t\n"
"RenderEvent 173 -26 0 0 0 0 t\n"
"MouseMoveEvent 173 -29 0 0 0 0 t\n"
"RenderEvent 173 -29 0 0 0 0 t\n"
"MouseMoveEvent 173 -30 0 0 0 0 t\n"
"RenderEvent 173 -30 0 0 0 0 t\n"
"MouseMoveEvent 173 -33 0 0 0 0 t\n"
"RenderEvent 173 -33 0 0 0 0 t\n"
"MouseMoveEvent 173 -36 0 0 0 0 t\n"
"RenderEvent 173 -36 0 0 0 0 t\n"
"MouseMoveEvent 173 -39 0 0 0 0 t\n"
"RenderEvent 173 -39 0 0 0 0 t\n"
"MouseMoveEvent 173 -42 0 0 0 0 t\n"
"RenderEvent 173 -42 0 0 0 0 t\n"
"MouseMoveEvent 173 -46 0 0 0 0 t\n"
"RenderEvent 173 -46 0 0 0 0 t\n"
"MouseMoveEvent 173 -50 0 0 0 0 t\n"
"RenderEvent 173 -50 0 0 0 0 t\n"
"MouseMoveEvent 173 -53 0 0 0 0 t\n"
"RenderEvent 173 -53 0 0 0 0 t\n"
"MouseMoveEvent 173 -56 0 0 0 0 t\n"
"RenderEvent 173 -56 0 0 0 0 t\n"
"MouseMoveEvent 173 -58 0 0 0 0 t\n"
"RenderEvent 173 -58 0 0 0 0 t\n"
"MouseMoveEvent 173 -60 0 0 0 0 t\n"
"RenderEvent 173 -60 0 0 0 0 t\n"
"MouseMoveEvent 173 -62 0 0 0 0 t\n"
"RenderEvent 173 -62 0 0 0 0 t\n"
"MouseMoveEvent 173 -63 0 0 0 0 t\n"
"RenderEvent 173 -63 0 0 0 0 t\n"
"MouseMoveEvent 173 -64 0 0 0 0 t\n"
"RenderEvent 173 -64 0 0 0 0 t\n"
"RightButtonReleaseEvent 173 -64 0 0 0 0 t\n"
"EndInteractionEvent 173 -64 0 0 0 0 t\n"
"RenderEvent 173 -64 0 0 0 0 t\n"
"LeaveEvent 173 -64 0 0 0 0 t\n"
"EnterEvent 171 4 0 0 0 0 t\n"
"MouseMoveEvent 171 4 0 0 0 0 t\n"
"MouseMoveEvent 172 15 0 0 0 0 t\n"
"MouseMoveEvent 173 23 0 0 0 0 t\n"
"MouseMoveEvent 173 30 0 0 0 0 t\n"
"MouseMoveEvent 173 37 0 0 0 0 t\n"
"MouseMoveEvent 174 44 0 0 0 0 t\n"
"MouseMoveEvent 174 48 0 0 0 0 t\n"
"MouseMoveEvent 174 53 0 0 0 0 t\n"
"MouseMoveEvent 174 59 0 0 0 0 t\n"
"MouseMoveEvent 174 63 0 0 0 0 t\n"
"MouseMoveEvent 174 67 0 0 0 0 t\n"
"MouseMoveEvent 174 71 0 0 0 0 t\n"
"MouseMoveEvent 174 74 0 0 0 0 t\n"
"MouseMoveEvent 174 76 0 0 0 0 t\n"
"MouseMoveEvent 174 79 0 0 0 0 t\n"
"MouseMoveEvent 174 81 0 0 0 0 t\n"
"MouseMoveEvent 174 84 0 0 0 0 t\n"
"MouseMoveEvent 174 87 0 0 0 0 t\n"
"MouseMoveEvent 173 90 0 0 0 0 t\n"
"MouseMoveEvent 172 93 0 0 0 0 t\n"
"MouseMoveEvent 172 96 0 0 0 0 t\n"
"MouseMoveEvent 170 98 0 0 0 0 t\n"
"MouseMoveEvent 169 100 0 0 0 0 t\n"
"MouseMoveEvent 169 101 0 0 0 0 t\n"
"MouseMoveEvent 167 104 0 0 0 0 t\n"
"MouseMoveEvent 166 106 0 0 0 0 t\n"
"MouseMoveEvent 164 108 0 0 0 0 t\n"
"MouseMoveEvent 162 110 0 0 0 0 t\n"
"MouseMoveEvent 160 114 0 0 0 0 t\n"
"MouseMoveEvent 160 115 0 0 0 0 t\n"
"MouseMoveEvent 158 117 0 0 0 0 t\n"
"MouseMoveEvent 157 119 0 0 0 0 t\n"
"MouseMoveEvent 157 121 0 0 0 0 t\n"
"MouseMoveEvent 155 123 0 0 0 0 t\n"
"MouseMoveEvent 154 125 0 0 0 0 t\n"
"MouseMoveEvent 154 127 0 0 0 0 t\n"
"MouseMoveEvent 154 129 0 0 0 0 t\n"
"MouseMoveEvent 153 130 0 0 0 0 t\n"
"MouseMoveEvent 152 132 0 0 0 0 t\n"
"MouseMoveEvent 152 133 0 0 0 0 t\n"
"MouseMoveEvent 152 134 0 0 0 0 t\n"
"MouseMoveEvent 152 135 0 0 0 0 t\n"
"MouseMoveEvent 152 137 0 0 0 0 t\n"
"MouseMoveEvent 152 138 0 0 0 0 t\n"
"MouseMoveEvent 152 139 0 0 0 0 t\n"
"MouseMoveEvent 152 140 0 0 0 0 t\n"
"MouseMoveEvent 152 141 0 0 0 0 t\n"
"MouseMoveEvent 152 142 0 0 0 0 t\n"
"MouseMoveEvent 152 143 0 0 0 0 t\n"
"MouseMoveEvent 152 144 0 0 0 0 t\n"
"MouseMoveEvent 151 144 0 0 0 0 t\n"
"MouseMoveEvent 151 145 0 0 0 0 t\n"
"MouseMoveEvent 151 146 0 0 0 0 t\n"
"MouseMoveEvent 151 147 0 0 0 0 t\n"
"MouseMoveEvent 151 148 0 0 0 0 t\n"
"MouseMoveEvent 150 148 0 0 0 0 t\n"
"MouseMoveEvent 150 149 0 0 0 0 t\n"
"MouseMoveEvent 149 149 0 0 0 0 t\n"
"MouseMoveEvent 149 150 0 0 0 0 t\n"
"LeftButtonPressEvent 149 150 0 0 0 0 t\n"
"RenderEvent 149 150 0 0 0 0 t\n"
"MouseMoveEvent 149 149 0 0 0 0 t\n"
"RenderEvent 149 149 0 0 0 0 t\n"
"MouseMoveEvent 149 148 0 0 0 0 t\n"
"RenderEvent 149 148 0 0 0 0 t\n"
"MouseMoveEvent 149 147 0 0 0 0 t\n"
"RenderEvent 149 147 0 0 0 0 t\n"
"LeftButtonReleaseEvent 149 147 0 0 0 0 t\n"
"RenderEvent 149 147 0 0 0 0 t\n"
"MouseMoveEvent 149 147 0 0 0 0 t\n"
"MouseMoveEvent 153 145 0 0 0 0 t\n"
"MouseMoveEvent 157 142 0 0 0 0 t\n"
"MouseMoveEvent 161 139 0 0 0 0 t\n"
"MouseMoveEvent 164 138 0 0 0 0 t\n"
"MouseMoveEvent 165 136 0 0 0 0 t\n"
"MouseMoveEvent 166 136 0 0 0 0 t\n"
"MouseMoveEvent 167 136 0 0 0 0 t\n"
"KeyPressEvent 167 136 0 0 113 1 q\n"
"CharEvent 167 136 0 0 113 1 q\n"
"ExitEvent 167 136 0 0 113 1 q\n"
;




// This callback is responsible for setting the angle label.
class vtkHandleCallback : public vtkCommand
{
public:
  static vtkHandleCallback *New()
    { return new vtkHandleCallback; }
  virtual void Execute(vtkObject*, unsigned long eid, void*)
    {
    if ( eid == vtkCommand::InteractionEvent )
      {
      double point1[3];
      this->Rep->GetWorldPosition(point1);
      std::cout << "Handle position: " << "("
           << point1[0] << ","
           << point1[1] << ","
           << point1[2] << ")" << std::endl;
      }
    }
  vtkFixedSizeHandleRepresentation3D *Rep;
  vtkHandleCallback():Rep(0) {}
};


// The actual test function
int TestFixedSizeHandleRepresentation3D( int argc, char *argv[] )
{
  vtkSmartPointer<vtkSphereSource> ss
    = vtkSmartPointer<vtkSphereSource>::New();
  ss->SetRadius( 10.0 );
  ss->SetCenter(0,0,0);
  ss->Update();

  // Create the RenderWindow, Renderer and both Actors
  //
  vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer< vtkRenderer >::New();
  vtkSmartPointer< vtkRenderWindow > renWin = vtkSmartPointer< vtkRenderWindow >::New();
  renWin->AddRenderer(ren);

  vtkSmartPointer< vtkRenderWindowInteractor > iren
    = vtkSmartPointer< vtkRenderWindowInteractor >::New();
  iren->SetRenderWindow(renWin);

  // Create a test pipeline showing a sphere and our handle on it.

  vtkSmartPointer< vtkPolyDataMapper > mapper
    = vtkSmartPointer< vtkPolyDataMapper >::New();
  mapper->SetInputConnection(ss->GetOutputPort());
  vtkSmartPointer< vtkActor > actor = vtkSmartPointer< vtkActor >::New();
  actor->SetMapper(mapper);

  // Create the widget and its representation

  vtkSmartPointer< vtkFixedSizeHandleRepresentation3D > rep
    = vtkSmartPointer< vtkFixedSizeHandleRepresentation3D >::New();
  rep->SetHandleSizeInPixels(10.0);
  rep->SetHandleSizeToleranceInPixels(1.0);
  rep->GetProperty()->SetColor(1,0,0);
  double p[3] = {0,0,10};
  rep->SetWorldPosition(p);

  vtkSmartPointer< vtkHandleWidget > widget
    = vtkSmartPointer< vtkHandleWidget >::New();
  widget->SetInteractor(iren);
  widget->SetDefaultRenderer(ren);
  widget->SetRepresentation(rep);

  // Print out the handle position when we interact with the widget

  vtkSmartPointer< vtkHandleCallback > mcbk
    = vtkSmartPointer< vtkHandleCallback >::New();
  mcbk->Rep = rep;
  widget->AddObserver(vtkCommand::InteractionEvent,mcbk);

  // Add the actors to the renderer, set the background and size

  ren->AddActor(actor);
  ren->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(300, 300);

  // render

  iren->Initialize();
  renWin->Render();
  widget->On();
  renWin->Render();

  return vtkTesting::InteractorEventLoop(
      argc, argv, iren, TestFixedSizeHandleRepresentation3DLog );
}
