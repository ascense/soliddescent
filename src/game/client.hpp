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

#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP

#include <SDL/SDL.h>

#include "../core/messaging/message.hpp"
#include "../core/messaging/msginterface.hpp"

#include "../renderer/model.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/texturedata.hpp"
#include "input.hpp"
#include "entity.hpp"


namespace SolidDescent { namespace Game {

class Client : public Core::MsgInterface {
public:
    Client();
    ~Client();

    void update(double delta);
    bool is_running();

    void callback(Core::Message* msg);

    void set_mouse_sensitivity(float factor);

    void get_camera_angle(float (*angles)[3]);
    void get_camera_position(float (*xyz)[3]);

    Renderer::Texture** get_skybox();

    Renderer::Texture *test_tex;
    Renderer::Model *test_mod;

private:
    void handle_input(double delta);

    void handle_events();
    void handle_mouse(SDL_Event* event);

    bool running;

    Input *input;

    Renderer::Texture **skybox;
    Entity *player;
};

}} // SolidDescent::Game

#endif // GAME_CLIENT_HPP
