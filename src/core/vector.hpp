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

#ifndef CORE_VECTOR_HPP
#define CORE_VECTOR_HPP


namespace SolidDescent { namespace Core {

struct Vec3f {
    float x, y, z;

    Vec3f() {};
    Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};
};

}} // SolidDescent::Core

#endif // CORE_VECTOR_HPP

