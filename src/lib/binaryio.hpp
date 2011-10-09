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

#ifndef LIB_BINARYIO_HPP
#define LIB_BINARYIO_HPP

#include <fstream>

#include "../core/exceptions.hpp"
#include "../core/vector.hpp"


namespace SolidDescent { namespace Lib {

int read_int(std::ifstream* stream);
float read_float(std::ifstream* stream);
std::string read_cstr(std::ifstream* stream, int maxlen);
Core::Vec3f read_vec3f(std::ifstream* stream);

void read_val(std::ifstream* stream, void* val, std::size_t len);
void check_stream(std::ifstream* stream);

}} // SolidDescent::Lib

#endif // LIB_BINARYIO_HPP
