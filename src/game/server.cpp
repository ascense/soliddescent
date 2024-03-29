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

#include "server.hpp"


namespace SolidDescent { namespace Game {

Server::Server() : running(true) {
    listen(Core::MSG_QUIT);
}


Server::~Server() {}


void Server::update(double time_delta) {}


bool Server::is_running() {
    return running;
}


void Server::callback(Core::Message* msg) {
    switch (msg->type) {
        case Core::MSG_QUIT:
            running = false;
            break;

        default:
            break;
    }
}


}} // SolidDescent::Game

