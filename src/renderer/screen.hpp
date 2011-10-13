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

#ifndef RENDERER_SCREEN_HPP
#define RENDERER_SCREEN_HPP

#include <cmath>
#include <GL/glew.h>
#include <SDL/SDL.h>

#include "../core/exceptions.hpp"
#include "../game/client.hpp"
#include "draw.hpp"


namespace SolidDescent { namespace Renderer {

class Screen {
public:
    Screen(Game::Client* client, int width, int height, bool fullscreen) throw (Core::SolidDescentException);
    ~Screen();

    void draw();

    void set_fov(int fov);

private:
    void set_gl_buffer(int col_bits, int depth_bits);
    bool set_video_mode(int width, int height, int bpp, bool fullscreen);
    void set_projection(int fov, double near, double far);
    void set_shading();

    void draw_sky();
    void draw_world();
    void draw_2d();

    void check_gl_err();

    Game::Client *game;

    SDL_Surface *surface;

    int width, height;
    bool fullscreen;
    double znear, zfar;
};

}} // SolidDescent::Renderer

#endif // RENDERER_SCREEN_HPP
