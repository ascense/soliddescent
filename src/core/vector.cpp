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

#include "vector.hpp"


namespace SolidDescent { namespace Core {

Vec3f::Vec3f() : x(0), y(0), z(0) {}
Vec3f::Vec3f(float* arr) : x(arr[0]), y(arr[1]), z(arr[2]) {};
Vec3f::Vec3f(float x, float y, float z) : x(x), y(y), z(z) {};


void Vec3f::read(float* arr) {
    x = arr[0];
    y = arr[1];
    z = arr[2];
}


void Vec3f::store(float* arr) {
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
}


void Vec3f::scale(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

}} // SolidDescent::Core
