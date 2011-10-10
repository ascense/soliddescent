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

#ifndef RENDERER_TEXTUREFMT_HPP
#define RENDERER_TEXTUREFMT_HPP

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <SDL/SDL.h>

#include "../../core/exceptions.hpp"
#include "../texturedata.hpp"


namespace SolidDescent { namespace Renderer {

enum TextureSrcFmt {TEX_BMP, TEX_TGA, TEX_UNSUPPORTED};

TextureData* load_texture(std::string path, const TextureFmt* internalfmt);
TextureData* load_texture(const char* path, TextureSrcFmt fmt, const TextureFmt* internalfmt);

TextureData* load_bmp(const char* path, const TextureFmt* internalfmt);
TextureData* load_tga(const char* path, const TextureFmt* internalfmt);

GLuint gen_texture(const TextureFmt* internalfmt);

}} // SolidDescent::Renderer

#endif // RENDERER_TEXTUREFMT_HPP
