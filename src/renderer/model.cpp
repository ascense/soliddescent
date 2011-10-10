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

#include "model.hpp"


namespace SolidDescent { namespace Renderer {

Model::~Model() {
    if (data != NULL)
        delete data;
}


void Model::load() throw (Core::SolidDescentException) {
    if (data != NULL)
        return;

    try {
        data = load_model(path);
    } catch (Core::SolidDescentException &e) {
        available = false;
        throw;
    }

    available = true;
}


void Model::unload() {
    if (data != NULL) {
        delete data;
        data = NULL;
    }

    available = true;
}


ModelData* Model::get_data() {
    ondemand_load();

    return data;
}


void Model::ondemand_load() {
    if (data != NULL || !available)
        return;

    try {
        load();
    } catch (Core::SolidDescentException &e) {
        Lib::log_error(&e, path);
    }
}

}} // SolidDescent::Renderer
