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

// TGA-Specific Magic Numbers
#define TGA_FORMAT_RGB 2


namespace SolidDescent { namespace Renderer {

TextureData* load_tga(const char* path, const TextureFmt* fmt) {
    TextureData *data = NULL;
    std::ifstream stream;

    struct TGAHeader {
        char id_length;
        char colormaptype;
        char datatype;

        uint16_t colormap_origin;
        uint16_t colormap_length;
        char colormap_depth;

        uint16_t x_origin;
        uint16_t y_origin;
        uint16_t width;
        uint16_t height;

        char bpp;
        char descriptor;
    } __attribute__((packed)) header;

    stream.open(path, std::ios::binary);
    if (!stream.good()) {
        stream.close();
        throw Core::SolidDescentException("Could not read texture file");
    }

    try {
        stream.read((char*) &header, sizeof(TGAHeader));

        // Only accept uncompressed RGB data
        if (header.datatype != TGA_FORMAT_RGB)
            throw Core::SolidDescentException("Unsupported texture format");

        GLenum pixelfmt;
        if (header.bpp == 24)
            pixelfmt = GL_RGB;
        else if (header.bpp == 32)
            pixelfmt = GL_RGBA;
        else
            throw Core::SolidDescentException("Unsupported texture format");

        // Seek past image id and possible colormap
        stream.seekg(header.id_length, std::ios::cur);
        if (header.colormaptype)
            stream.seekg(header.colormap_length * header.colormap_depth, std::ios::cur);

        // Read texture data
        GLuint handle = gen_texture(fmt);
        data = new TextureData(handle, header.width, header.height);

        // Convert pixel-data to little-endian
        char pixels[header.width * header.height * (header.bpp / 8)];
        for (int i = 0; i < header.width * header.height; ++i) {
            for (int j = (i + 1) * (header.bpp / 8) - (header.bpp / 16); j >= i * (header.bpp / 8); --j)
                stream.read(&pixels[j], 1);
            if (header.bpp == 32)
                stream.read(&pixels[i * 4 + 3], 1);
        }

        glTexImage2D(GL_TEXTURE_2D, 0, fmt->fmt, header.width, header.height, 0, pixelfmt, GL_UNSIGNED_BYTE, pixels);

    } catch (std::exception &e) {
        stream.close();
        throw;
    }

    return data;
}

}} // SolidDescent::Renderer
