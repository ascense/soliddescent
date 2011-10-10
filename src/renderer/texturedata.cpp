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

#include "texturedata.hpp"


namespace SolidDescent { namespace Renderer {

TextureData::TextureData(GLuint handle, int width, int height)
        : handle(handle), width(width), height(height) {}


TextureData::~TextureData() {
    if (handle > 0)
        glDeleteTextures(1, &handle);
}


void TextureData::use() {
   if (handle > 0)
        glBindTexture(GL_TEXTURE_2D, handle);
    else
        glBindTexture(GL_TEXTURE_2D, 0);
}

}} // SolidDescent::Renderer
