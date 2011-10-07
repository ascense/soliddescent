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

#include <string>
#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL/SDL.h>


namespace SolidDescent { namespace Renderer {

struct TextureFmt {
    GLenum fmt;
    GLint wrap;
    GLint filter;
};

const TextureFmt TEX_RGB = {GL_RGB, GL_REPEAT, GL_LINEAR};
const TextureFmt TEX_RGBA = {GL_RGBA, GL_REPEAT, GL_LINEAR};
const TextureFmt TEX_SKY = {GL_RGB, GL_CLAMP, GL_NEAREST};


class Texture {
public:
    Texture(std::string path, const TextureFmt* format);
    ~Texture();

    bool load();
    void unload();

    void use();
    bool available();

private:
    int width, height;
    std::string path;

    bool is_available;

    const TextureFmt* fmt;
    GLuint handle;
};

}} // SolidDescent::Renderer

#endif // RENDERER_TEXTURE_HPP
