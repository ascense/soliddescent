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

#include "texturefmt.hpp"


namespace SolidDescent { namespace Renderer {

TextureData* load_texture(std::string path, const TextureFmt* internalfmt) {
    // Determine format
    TextureSrcFmt fmt;

    size_t ext_start = path.length() - 3;
    if (ext_start <= 0)
        throw Core::SolidDescentException("Failed to determine texture format");

    if (path.compare(ext_start, 3, "bmp") == 0)
        fmt = TEX_BMP;
    else if (path.compare(ext_start, 3, "tga") == 0)
        fmt = TEX_TGA;
    else
        fmt = TEX_UNSUPPORTED;

    return load_texture(path.c_str(), fmt, internalfmt);
}


TextureData* load_texture(const char* path, TextureSrcFmt fmt, const TextureFmt* internalfmt) {
    TextureData *data;

    switch (fmt) {
        case TEX_BMP:
            data = load_bmp(path, internalfmt);
            break;

        case TEX_TGA:
            data = load_tga(path, internalfmt);
            break;

        default:
            throw Core::SolidDescentException("Unsupported texture format");
    }

    if (!data)
        throw Core::SolidDescentException("Failed to load texture data");

    return data;
}


GLuint gen_texture(const TextureFmt* fmt) {
    GLuint handle;

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, fmt->wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, fmt->wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, fmt->min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, fmt->mag_filter);

    if (GLEW_VERSION_1_3)
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    return handle;
}

}} // SolidDescent::Renderer
