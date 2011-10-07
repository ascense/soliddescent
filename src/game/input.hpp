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

#ifndef GAME_INPUT_HPP
#define GAME_INPUT_HPP

#include <SDL/SDL.h>


namespace SolidDescent { namespace Game {

enum GameKey {
    K_FORWARD, K_BACK, K_LEFT, K_RIGHT,
    K_USE, K_JUMP,
    K_QUIT,
    K_MAP_LENGTH // Hack for getting amount of GameKey values
};


class Input {
public:
    Input();
    ~Input();

    void set_mouse_sensitivity(float factor);
    void set_key_down(SDLKey* key);
    void set_key_up(SDLKey* key);

    bool key_down(GameKey key);

    void clear_keys();

    float m_xfactor, m_yfactor;

private:
    void load_keymap();

    int key_to_gamekey(SDLKey* key);

    SDLKey *keymap;
    bool *keydown;

    float m_yaw, m_pitch;
};

}} // SolidDescent::Game

#endif // GAME_INPUT_HPP
