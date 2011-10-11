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

#include "msgserver.hpp"


namespace SolidDescent { namespace Core {

MsgCallback::~MsgCallback() {}


MsgServer* MsgServer::singleton = NULL;


MsgServer::MsgServer() : msg_head(NULL), msg_tail(NULL) {
    cb_array = new MsgCallback*[MSG_MAP_LENGTH]();
}


MsgServer::~MsgServer() {
    MsgCallback *cb, *cb_next;
    for (int i = 0; i < MSG_MAP_LENGTH; ++i) {
        cb_next = cb_array[i];

        while ((cb = cb_next) != NULL) {
            cb_next = cb->next;
            delete cb;
        }
    }
    delete [] cb_array;
}


MsgServer* MsgServer::get_inst() {
    if (!singleton)
        singleton = new MsgServer();

    return singleton;
}


void MsgServer::destroy() {
    if (singleton != NULL)
        delete singleton;
}


void MsgServer::post(Message* msg) {
    if (msg_head == NULL)
        msg_tail = msg;
    else
        msg_head->next = msg;

    msg_head = msg;
}


void MsgServer::process() {
    Message *tail;
    MsgCallback *cb;

    while ((tail = msg_tail) != NULL) {
        msg_tail = tail->next;

        cb = cb_array[tail->type];
        while (cb != NULL) {
            cb->cb->callback(tail);
            cb = cb->next;
        }

        delete tail;
    }
}


void MsgServer::add_listener(MessageType msg_type, MsgInterface* cb) {
    MsgCallback *msg_cb = new MsgCallback(cb);

    if (cb_array[msg_type] == NULL) {
        cb_array[msg_type] = msg_cb;
    } else {
        MsgCallback *old_cb = cb_array[msg_type];
        while (old_cb->next != NULL)
            old_cb = old_cb->next;

        old_cb->next = msg_cb;
    }
}


void MsgServer::drop_listener(MessageType msg_type, MsgInterface* cb) {
    if (cb_array[msg_type] == NULL)
        return;

    MsgCallback *msg_cb;
    if (cb_array[msg_type]->cb == cb) {
        msg_cb = cb_array[msg_type];
        cb_array[msg_type] = msg_cb->next;
        delete cb;
    } else {
        msg_cb = cb_array[msg_type];
        while (msg_cb->next != NULL && msg_cb->next->cb != cb)
            msg_cb = msg_cb->next;

        if (msg_cb->next == NULL)
            return;

        MsgCallback *cb_next = msg_cb->next->next;
        delete msg_cb->next;
        msg_cb->next = cb_next;
    }
}

}} // SolidDescent::Core
