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

Entity::Entity() : speed(8), model(NULL) {}


Entity::Entity(float x, float y, float z)
        : speed(8), pos(x, y, z), model(NULL) {}


Entity::~Entity() {}


void Entity::translate(float distance) {
    float rad = Lib::to_radians(rot.y);
    pos.x += (float) std::sin(rad) * distance;
    pos.z -= (float) std::cos(rad) * distance;
}


void Entity::strafe(float distance) {
    float rad = Lib::to_radians(rot.y - 90);
    pos.x += (float) std::sin(rad) * distance;
    pos.z -= (float) std::cos(rad) * distance;
}


void Entity::tilt(float degrees) {
    rot.x += degrees;
    if (rot.x > 90)
        rot.x = 90;
    else if (rot.x < -90)
        rot.x = -90;
}


void Entity::turn(float degrees) {
    rot.y += degrees;
    if (rot.y < 0)
        rot.y += 360;
    else if (rot.y > 360)
        rot.y -= 360;
}

}} // SolidDescent::Game
