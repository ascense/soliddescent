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

Texture::Texture(std::string path, const TextureFmt* format) {
    this->path = path;
    fmt = format;

    // assume that the texture is OK for loading
    is_available = true;

    handle = 0;
}


Texture::~Texture() {
    unload();
}


bool Texture::load() {
    SDL_Surface* surf = SDL_LoadBMP(path.c_str());
    if (!surf)
        return false;

    // verify that both width & height are powers of 2
    if ((surf->w & (surf->w - 1)) != 0 || (surf->h & (surf->h - 1)) != 0) {
        SDL_FreeSurface(surf);
        return false;
    }

    // verify that the texture is in 24-bpp format
    if (surf->format->BitsPerPixel != 24) {
        SDL_FreeSurface(surf);
        return false;
    }

    width = surf->w;
    height = surf->h;

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, fmt->wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, fmt->wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, fmt->filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, fmt->filter);

    glTexImage2D(GL_TEXTURE_2D, 0, fmt->fmt, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, surf->pixels);

    SDL_FreeSurface(surf);

    return true;
}


void Texture::unload() {
    if (handle > 0)
        glDeleteTextures(1, &handle);
}


void Texture::use() {
    if (handle <= 0)
        is_available = load();

    if (handle > 0)
        glBindTexture(GL_TEXTURE_2D, handle);
    else
        glBindTexture(GL_TEXTURE_2D, 0);
}


bool Texture::available() {
    return ((handle > 0) || is_available);
}

}} // SolidDescent::Renderer
