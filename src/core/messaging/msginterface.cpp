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

#include "msginterface.hpp"


namespace SolidDescent { namespace Core {

void MsgInterface::listen(MessageType type) {
    MsgServer::get_inst()->add_listener(type, this);
}


void MsgInterface::release(MessageType type) {
    MsgServer::get_inst()->drop_listener(type, this);
}


void MsgInterface::post(Message* msg) {
    MsgServer::get_inst()->post(msg);
}


void MsgInterface::post(MessageType type) {
    Message *msg = new Message(type);
    MsgServer::get_inst()->post(msg);
}


void MsgInterface::post(MessageType type, void* data, size_t data_len) {
    Message *msg = new Message(type);
    msg->data_len = data_len;

    msg->data = std::malloc(data_len);
    if (msg->data != NULL)
        std::memcpy(msg->data, data, data_len);

    MsgServer::get_inst()->post(msg);
}


void MsgInterface::post(MessageType type, float val) {
    post(type, &val, sizeof(float));
}


void MsgInterface::post(MessageType type, int val) {
    post(type, &val, sizeof(int));
}

}} // SolidDescent::Core
