/**
* Copyright (C) 2011 Henry Carlson
*
* This file is part of the SolidDescent engine.
*
* The SolidDescent engine is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* The SolidDescent engine is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RENDERER_DRAW_HPP
#define RENDERER_DRAW_HPP

#include <GL/gl.h>

#include "texture.hpp"
#include "model.hpp"
#include "mesh.hpp"


namespace SolidDescent { namespace Renderer {

void draw_model(Model* mod);
void draw_mesh(Mesh* mesh);
void draw_cube(int x, int y, int z, int width, int height, int depth);
void draw_skybox(Texture** skybox);

}} // SolidDescent::Renderer

#endif // RENDERER_DRAWLIB_HPP
