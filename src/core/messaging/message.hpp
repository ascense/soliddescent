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

#ifndef CORE_MESSAGE_HPP
#define CORE_MESSAGE_HPP

#include <cstddef>


namespace SolidDescent { namespace Core {

enum MessageType {
    // Core:
    MSG_SET_MAXFPS,
    MSG_QUIT,
    // Renderer:
    MSG_R_SET_FOV,
    MSG_R_REINIT,
    // Keep this last:
    MSG_MAP_LENGTH
};


struct Message {
    MessageType type;
    size_t data_len;
    void *data;

    Message *next;

    Message(MessageType type) : type(type), data_len(0), data(NULL), next(NULL) {}
    ~Message();
};

}} // SolidDescent::Core

#endif // CORE_MESSAGE_HPP
