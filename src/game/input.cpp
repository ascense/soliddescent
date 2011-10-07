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

#include "input.hpp"


namespace SolidDescent { namespace Game {

Input::Input() {
    keymap = new SDLKey[K_MAP_LENGTH];
    keydown = new bool[K_MAP_LENGTH];

    m_pitch = m_yaw = 0.22f;

    load_keymap();
    set_mouse_sensitivity(10);
    clear_keys();
}


Input::~Input() {
    delete [] keymap;
    delete [] keydown;
}


void Input::set_mouse_sensitivity(float factor) {
    m_xfactor = m_yaw * (factor / 10);
    m_yfactor = m_pitch * (factor / 10);
}


void Input::set_key_down(SDLKey* key) {
    int gk = key_to_gamekey(key);
    if (gk < 0)
        return;

    keydown[gk] = true;
}


void Input::set_key_up(SDLKey* key) {
    int gk = key_to_gamekey(key);
    if (gk < 0)
        return;

    keydown[gk] = false;
}


bool Input::key_down(GameKey key) {
    if (key == K_MAP_LENGTH)
        return false;

    return keydown[key];
}


void Input::clear_keys() {
    for (int i = 0; i < K_MAP_LENGTH; ++i)
        keydown[i] = false;
}


void Input::load_keymap() {
    keymap[K_FORWARD] = SDLK_w;
    keymap[K_BACK] = SDLK_s;
    keymap[K_LEFT] = SDLK_a;
    keymap[K_RIGHT] = SDLK_d;

    keymap[K_USE] = SDLK_f;
    keymap[K_JUMP] = SDLK_SPACE;

    keymap[K_QUIT] = SDLK_ESCAPE;
}


int Input::key_to_gamekey(SDLKey* key) {
    for (int i = 0; i < K_MAP_LENGTH; ++i) {
        if (keymap[i] == *key)
            return i;
    }

    return -1;
}

}} // SolidDescent::Game
