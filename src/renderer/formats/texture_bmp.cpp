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

TextureData* load_bmp(const char* path, const TextureFmt* fmt) {
    TextureData* tex;
    SDL_Surface* surf = SDL_LoadBMP(path);

    if (!surf)
        throw Core::SolidDescentException("Could not read texture file");

    // verify that both width & height are powers of 2
    if ((surf->w & (surf->w - 1)) != 0 || (surf->h & (surf->h - 1)) != 0) {
        SDL_FreeSurface(surf);
        throw Core::SolidDescentException("Texture size is not a power of two");
    }

    // verify that the texture is in 24-bpp format
    if (surf->format->BitsPerPixel != 24) {
        SDL_FreeSurface(surf);
        throw Core::SolidDescentException("Texture is of unsupported format");
    }

    GLuint handle = gen_texture(fmt);
    tex = new TextureData(handle, surf->w, surf->h);

    // Annoying surface has a flipped y-axis, so let's flip it again... :|
    int bytes = surf->format->BitsPerPixel / 8;
    char* pixels = new char[surf->w * surf->h * bytes];
    for (int y = 0; y < surf->h; ++y) {
        for (int x = 0; x < surf->w; ++x) {
            for (int i = 0; i < bytes; ++i)
                pixels[(x + (y * surf->w)) * bytes + i] = ((char*) (surf->pixels))[(x + ((surf->h - y - 1) * surf->w)) * bytes + i];
        }
    }

    SDL_FreeSurface(surf);

    glTexImage2D(GL_TEXTURE_2D, 0, fmt->fmt, tex->height, tex->width, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

    delete [] pixels;

    return tex;
}

}} // SolidDescent::Renderer
