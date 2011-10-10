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

#include "../soliddescent.hpp"


namespace SolidDescent { namespace Core {

Engine::Engine() {
    server = new Game::Server();
    client = new Game::Client();

    try {
        screen = new Renderer::Screen(client, 800, 600, false);
    } catch (std::exception& e) {
        delete server;
        delete client;
        throw;
    }

    set_maxfps(120);
    client->set_mouse_sensitivity(5);
    // screen->set_fov(90);

    frame_time = SDL_GetTicks();
}


Engine::~Engine() {
    delete client;
    delete server;

    delete screen;
}


void Engine::run() {
    double delta;

    while (client->is_running()) {
        // Timing
        delta = handle_timing();

        // Server
        if (server->is_running())
            server->update(delta);

        // Client
        client->update(delta);
        screen->draw();
    }
}


double Engine::handle_timing() {
    if (frame_millis > 0) {
        long delta_offset = frame_time + frame_millis - SDL_GetTicks();
        if (delta_offset > Engine::MIN_SLEEP_INTERVAL)
            SDL_Delay(delta_offset);
    }

    double time_delta = (SDL_GetTicks() - frame_time) / 1000.0;
    frame_time = SDL_GetTicks();

    return time_delta;
}


void Engine::set_maxfps(int fps) {
    if (fps <= 0 || fps > 1000)
        frame_millis = -1;
    else
        frame_millis = 1000 / fps;
}

}} // SolidDescent::Core
