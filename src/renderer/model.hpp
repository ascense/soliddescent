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

#ifndef RENDERER_MODEL_HPP
#define RENDERER_MODEL_HPP

#include <string>


namespace SolidDescent { namespace Renderer {

struct ModelTag {
};

struct ModelFrame {
};

class Model {
public:
    Model(std::string name);
    ~Model();

private:
    std::string name;
};

}} // SolidDescent::Renderer

#endif // RENDERER_MODEL_HPP
