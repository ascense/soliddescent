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

#ifndef CORE_MSGLISTENER_HPP
#define CORE_MSGLISTENER_HPP

#include <cstdlib>
#include <cstring>

#include "message.hpp"
#include "msgserver.hpp"


namespace SolidDescent { namespace Core {

class MsgInterface {
public:
    void listen(MessageType type);
    void release(MessageType type);

    void post(Message* msg);
    void post(MessageType type);
    void post(MessageType type, void* data, size_t data_len);
    void post(MessageType type, float val);
    void post(MessageType type, int val);

    virtual void callback(Message* msg) = 0;
};

}} // SolidDescent::Core

#endif // CORE_MSGLISTENER_HPP
