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

#ifndef CORE_MSGSERVER_HPP
#define CORE_MSGSERVER_HPP

#include "message.hpp"
#include "msginterface.hpp"


namespace SolidDescent { namespace Core {

class MsgInterface;


struct MsgCallback {
    MsgInterface *cb;
    MsgCallback *next;

    MsgCallback(MsgInterface* cb) : cb(cb), next(NULL) {}
    ~MsgCallback();
};


class MsgServer {
public:
    static MsgServer* get_inst();
    static void destroy();

    void post(Message* msg);
    void process();

    void add_listener(MessageType msg_type, MsgInterface* cb);
    void drop_listener(MessageType msg_type, MsgInterface* cb);

protected:
    MsgServer();
    ~MsgServer();

    static MsgServer *singleton;
    MsgCallback **cb_array;
    Message *msg_head;
    Message *msg_tail;
};

}} // SolidDescent::Core

#endif // CORE_MSGSERVER_HPP
