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

#include "texture.hpp"


namespace SolidDescent { namespace Renderer {

Texture::Texture(std::string path, const TextureFmt* fmt)
    : Core::Resource(path), data(NULL), internal_fmt(fmt) {}


Texture::~Texture() {
    if (data != NULL)
        delete data;
}


void Texture::load() throw (Core::SolidDescentException) {
    if (data != NULL)
        return;

    try {
        data = load_texture(path.c_str(), internal_fmt);
    } catch (Core::SolidDescentException &e) {
        available = false;
        throw;
    }

    available = true;
}


void Texture::unload() {
    if (data != NULL) {
        delete data;
        data = NULL;
    }

    available = true;
}


void Texture::use() {
    ondemand_load();

    if (data != NULL)
        data->use();
}


TextureData* Texture::get_data() {
    ondemand_load();

    return data;
}


void Texture::ondemand_load() {
    if (data != NULL || !available)
        return;

    try {
        load();
    } catch (Core::SolidDescentException &e) {
        Lib::log_error(&e, path);
    }
}

}} // SolidDescent::Renderer
