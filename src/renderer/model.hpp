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

#include "../core/resource.hpp"
#include "../lib/logging.hpp"

#include "modeldata.hpp"
#include "formats/modelfmt.hpp"


namespace SolidDescent { namespace Renderer {

class Model : public Core::Resource {
public:
    Model(std::string path) : Core::Resource(path), data(NULL) {};
    ~Model();

    void load() throw (Core::SolidDescentException);
    void unload();

    ModelData* get_data();

private:
    void ondemand_load();

    ModelData *data;
};

}} // SolidDescent::Renderer

#endif // RENDERER_MODEL_HPP
