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

#ifndef RENDERER_TEXTURE_HPP
#define RENDERER_TEXTURE_HPP

#include "../core/resource.hpp"
#include "../lib/logging.hpp"

#include "texturedata.hpp"
#include "formats/texturefmt.hpp"


namespace SolidDescent { namespace Renderer {

class Texture : public Core::Resource {
public:
    Texture(std::string path, const TextureFmt* fmt);
    ~Texture();

    void load() throw (Core::SolidDescentException);
    void unload();

    void use();

    TextureData* get_data();

private:
    void ondemand_load();

    TextureData *data;
    const TextureFmt *internal_fmt;
};

}} // SolidDescent::Renderer

#endif // RENDERER_TEXTURE_HPP
