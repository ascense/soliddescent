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

#ifndef RENDERER_LOADMODEL_HPP
#define RENDERER_LOADMODEL_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "../lib/binaryio.hpp"
#include "../core/exceptions.hpp"
#include "model.hpp"
#include "mesh.hpp"

// MD3-Specific Magic Numbers
#define MD3_IDENT 0x49445033
#define MD3_MAX_QPATH 64


namespace SolidDescent { namespace Renderer {

enum ModelFmt {MOD_MD3};


Model* load_model(std::string path, ModelFmt fmt);

Model* load_md3(std::ifstream* stream);

}} // SolidDescent::Renderer

#endif // RENDERER_LOADMODEL_HPP
