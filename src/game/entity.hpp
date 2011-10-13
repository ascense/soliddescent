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

#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <cmath>

#include "../lib/math.hpp"
#include "../core/vector.hpp"
#include "../renderer/model.hpp"


namespace SolidDescent { namespace Game {

class Entity {
public:
    Entity();
    Entity(float x, float y, float z);
    ~Entity();

    void turn(float degrees);
    void tilt(float degrees);

    void translate(float distance);
    void strafe(float distance);

    float speed;
    Core::Vec3f pos;
    Core::Vec3f rot;

    // Entity doesn't take ownership of model
    Renderer::Model* model;
};

}} // SolidDescent::Game

#endif // GAME_ENTITY_HPP
