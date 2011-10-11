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

#ifndef CORE_ENGINE_HPP
#define CORE_ENGINE_HPP

#include "exceptions.hpp"
#include "messaging/msgserver.hpp"

#include "../renderer/screen.hpp"
#include "../game/server.hpp"
#include "../game/client.hpp"


namespace SolidDescent { namespace Core {

class Engine {
public:
    Engine();
    ~Engine();

    void run();
    void set_maxfps(int fps);

    // only sleep if more than 5 ms until next frame
    static const int MIN_SLEEP_INTERVAL = 5;

private:
    double handle_timing();

    Renderer::Screen *screen;
    Game::Server *server;
    Game::Client *client;

    long frame_time;
    int frame_millis;
};

}} // SolidDescent::Core

#endif // CORE_ENGINE_HPP
