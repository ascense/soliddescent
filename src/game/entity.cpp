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

#include "entity.hpp"


namespace SolidDescent { namespace Game {

Entity::Entity(float x, float y, float z) {
    heading = pitch = roll = 0;

    this->x = x;
    this->y = y;
    this->z = z;

    this->speed = 8;
}


Entity::~Entity() {}


void Entity::translate(float distance) {
    float rad = Lib::to_radians(heading);
    x += (float) std::sin(rad) * distance;
    z -= (float) std::cos(rad) * distance;
}


void Entity::strafe(float distance) {
    float rad = Lib::to_radians(heading - 90);
    x += (float) std::sin(rad) * distance;
    z -= (float) std::cos(rad) * distance;
}


void Entity::turn(float degrees) {
    heading += degrees;
    if (heading < 0)
        heading += 360;
    else if (heading > 360)
        heading -= 360;
}


void Entity::tilt(float degrees) {
    pitch += degrees;
    if (pitch > 90)
        pitch = 90;
    else if (pitch < -90)
        pitch = -90;
}

}} // SolidDescent::Game
