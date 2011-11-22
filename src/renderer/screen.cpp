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

#include "screen.hpp"


namespace SolidDescent { namespace Renderer {

Screen::Screen(Game::Client* client, int width, int height, bool fullscreen) throw (Core::SolidDescentException) {
    game = client;

    znear = 0.5;
    zfar = 1500;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw Core::CriticalError("Failed to initialize SDL");

    if (!set_video_mode(width, height, -1, fullscreen)) {
        SDL_Quit();
        throw Core::SolidDescentException("Failed to set video mode for new window");
    }

    if (GLEW_OK != glewInit()) {
        SDL_Quit();
        throw Core::CriticalError("Failed to initialize OpenGL extension wrangler");
    }

    SDL_WM_SetCaption("Solid Descent Engine Demo", "SolidDescent");
    set_shading();

    listen(Core::MSG_R_SET_WIDTH);
    listen(Core::MSG_R_SET_HEIGHT);
    listen(Core::MSG_R_SET_FULLSCREEN);
    listen(Core::MSG_R_SET_FOV);
    listen(Core::MSG_R_REINIT);
}


Screen::~Screen() {
    SDL_FreeSurface(surface);
    SDL_Quit();
}


void Screen::draw() {
    Core::Vec3f* cam;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glLoadIdentity();

    cam = game->get_camera_angle();
    glRotatef(cam->x, 1.0f, 0.0f, 0.0f);
    glRotatef(cam->y, 0.0f, 1.0f, 0.0f);
    glRotatef(cam->z, 0.0f, 0.0f, 1.0f);

    draw_sky();

    cam = game->get_camera_position();
    glTranslatef(-cam->x, -cam->y, -cam->z);

    draw_world();
    draw_2d();

    SDL_GL_SwapBuffers();
}


void Screen::callback(Core::Message* msg) {
    switch (msg->type) {
        case Core::MSG_R_SET_WIDTH:
            this->width = *((int*) (msg->data));
            break;

        case Core::MSG_R_SET_HEIGHT:
            this->height = *((int*) (msg->data));
            break;

        case Core::MSG_R_SET_FULLSCREEN:
            this->fullscreen = (*((bool*) (msg->data)));
            break;

        case Core::MSG_R_SET_FOV:
            set_fov(*((int*) (msg->data)));
            break;

        case Core::MSG_R_REINIT:
            set_video_mode(width, height, 0, fullscreen);
            set_shading(); // OpenGL context gets reset on Windows, so reinitialize
            break;

        default:
            break;
    }
}


void Screen::draw_sky() {
    draw_skybox(game->get_skybox());
}


void Screen::draw_world() {
    game->test_tex->use();
    draw_cube(-8, -8, -64, 32, 32, 32);

    draw_model(game->test_mod, 0, 0, 0, 0, 0, 0);
}


void Screen::draw_2d() {
}


// Change the screen geometry and fullscreen mode
bool Screen::set_video_mode(int width, int height, int bpp, bool fullscreen) {
    int flags = SDL_OPENGL;
    if (fullscreen)
        flags |= SDL_FULLSCREEN;

    // query SDL for the current BPP value, if no specific BPP was requested
    if (bpp < 0) {
        const SDL_VideoInfo *info = SDL_GetVideoInfo();
        if (!info)
            bpp = 24;
        else
            bpp = info->vfmt->BitsPerPixel;
    }

    // attempt to request buffers of 8 bits per color, 16 for depth
    set_gl_buffer(8, 16);
    surface = SDL_SetVideoMode(width, height, bpp, flags);

    // some systems only allow for 6 bits per color, so try that instead
    if (!surface) {
        set_gl_buffer(6, 16);
        surface = SDL_SetVideoMode(width, height, bpp, flags);
    }

    // failed to find an acceptable video mode
    if (!surface)
        return false;

    this->width = width;
    this->height = height;
    this->fullscreen = fullscreen;

    // for now, exit incase doublebuffering was not supported
    int dbuf;
    if (SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &dbuf) < 0 || dbuf != 1) {
        SDL_FreeSurface(surface);
        return false;
    }

    set_projection(90, znear, zfar);

    set_mouse_grab(true);

    return true;
}


// Set OpenGL buffer sizes requested by SDL
void Screen::set_gl_buffer(int col_bits, int depth_bits) {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, col_bits);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, col_bits);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, col_bits);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth_bits);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}


// Recalculate the view frustum settings for projection matrix
void Screen::set_projection(int fov, double near, double far) {
    if (znear != near)
        znear = near;
    if (zfar != far)
        zfar = far;

    GLdouble aspect = (double) (height) / (double) (width);
    GLdouble top = std::tan(fov * M_PI / 360.0) * near * aspect;
    GLdouble right = std::tan(fov * M_PI / 360.0) * near;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-right, right, -top, top, near, far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Set the default shading options
void Screen::set_shading() {
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

    glShadeModel(GL_SMOOTH);
    glClearColor(0, 0, 0, 0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}


void Screen::set_fov(int fov) {
    set_projection(fov, znear, zfar);
}


void Screen::set_mouse_grab(bool grabbed) {
    if (grabbed) {
        SDL_ShowCursor(0);
        SDL_WM_GrabInput(SDL_GRAB_ON);
    } else {
        SDL_ShowCursor(1);
        SDL_WM_GrabInput(SDL_GRAB_OFF);
    }
}


void Screen::check_gl_err() {
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR)
        throw Core::CriticalError("OpenGL Error, code " + err);
}

}} // SolidDescent::Renderer
