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

#include "client.hpp"


namespace SolidDescent { namespace Game {

Client::Client() {
    running = true;

    input = new Input();
    player = new Entity(0, 0, 0);
    player->speed = 32;

    skybox = new Renderer::Texture*[6];
    skybox[0] = new Renderer::Texture("./gfx/sky_north.bmp", &Renderer::TEX_SKY);
    skybox[1] = new Renderer::Texture("./gfx/sky_east.bmp", &Renderer::TEX_SKY);
    skybox[2] = new Renderer::Texture("./gfx/sky_south.bmp", &Renderer::TEX_SKY);
    skybox[3] = new Renderer::Texture("./gfx/sky_west.bmp", &Renderer::TEX_SKY);
    skybox[4] = new Renderer::Texture("./gfx/sky_up.bmp", &Renderer::TEX_SKY);
    skybox[5] = new Renderer::Texture("./gfx/sky_down.bmp", &Renderer::TEX_SKY);

    test_tex = new Renderer::Texture("./gfx/test.bmp", &Renderer::TEX_RGB);
    test_mod = new Renderer::Model("./models/test.md3");

    listen(Core::MSG_QUIT);
    listen(Core::MSG_G_SET_SENS);
}


Client::~Client() {
    delete test_tex;
    delete test_mod;

    for (int i = 0; i < 6; ++i) {
        if (skybox[i] != NULL)
            delete skybox[i];
    }
    delete [] skybox;

    delete input;
    delete player;
}


void Client::update(double delta) {
    handle_events();
    handle_input(delta);
}


bool Client::is_running() {
    return running;
}


void Client::set_mouse_sensitivity(float factor) {
    input->set_mouse_sensitivity(factor);
}


void Client::get_camera_angle(float (*angles)[3]) {
    (*angles)[0] = player->pitch; // X
    (*angles)[1] = player->heading; // Y
    (*angles)[2] = player->roll; // Z
}


void Client::get_camera_position(float (*pos)[3]) {
    (*pos)[0] = player->x;
    (*pos)[1] = player->y;
    (*pos)[2] = player->z;
}


Renderer::Texture** Client::get_skybox() {
    return skybox;
}


void Client::callback(Core::Message* msg) {
    switch (msg->type) {
        case Core::MSG_QUIT:
            running = false;
            break;

        case Core::MSG_G_SET_SENS:
            set_mouse_sensitivity(*((float*) (msg->data)));
            break;

        default:
            break;
    }
}


void Client::handle_input(double delta) {
    if (input->key_down(K_FORWARD))
        player->translate(delta * player->speed);
    if (input->key_down(K_BACK))
        player->translate(delta * -player->speed);
    if (input->key_down(K_LEFT))
        player->strafe(delta * player->speed);
    if (input->key_down(K_RIGHT))
        player->strafe(delta * -player->speed);

    if (input->key_down(K_JUMP))
        player->y += delta * player->speed;
    if (input->key_down(K_CROUCH))
        player->y += delta * -player->speed;

    if (input->key_down(K_QUIT))
        running = false;
}


void Client::handle_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_MOUSEMOTION:
                handle_mouse(&event);
                break;

            case SDL_KEYDOWN:
                input->set_key_down(&event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                input->set_key_up(&event.key.keysym.sym);
                break;

            default:
                break;
        }
    }
}


void Client::handle_mouse(SDL_Event* event) {
    player->turn(event->motion.xrel * input->m_xfactor);
    player->tilt(event->motion.yrel * input->m_yfactor);
}

}} // SolidDescent::Game
