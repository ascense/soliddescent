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

#include "draw.hpp"


namespace SolidDescent { namespace Renderer {

void draw_cube(int x, int y, int z, int width, int height, int depth) {
    int TEX_SCALE = 16;

    glBegin(GL_QUADS);

    // Front
    glTexCoord2f(0, height / TEX_SCALE);
    glVertex3i(x + width, y + height, z + depth);
    glTexCoord2f(width / TEX_SCALE, height / TEX_SCALE);
    glVertex3i(x, y + height, z + depth);
    glTexCoord2f(width / TEX_SCALE, 0);
    glVertex3i(x, y, z + depth);
    glTexCoord2f(0, 0);
    glVertex3i(x + width, y, z + depth);

    // Right
    glTexCoord2f(0, height / TEX_SCALE);
    glVertex3i(x + width, y + height, z);
    glTexCoord2f(width / TEX_SCALE, height / TEX_SCALE);
    glVertex3i(x + width, y + height, z + depth);
    glTexCoord2f(width / TEX_SCALE, 0);
    glVertex3i(x + width, y, z + depth);
    glTexCoord2f(0, 0);
    glVertex3i(x + width, y, z);

    // Back
    glTexCoord2f(0, height / TEX_SCALE);
    glVertex3i(x, y + height, z);
    glTexCoord2f(width / TEX_SCALE, height / TEX_SCALE);
    glVertex3i(x + width, y + height, z);
    glTexCoord2f(width / TEX_SCALE, 0);
    glVertex3i(x + width, y, z);
    glTexCoord2f(0, 0);
    glVertex3i(x, y, z);

    // Left
    glTexCoord2f(0, height / TEX_SCALE);
    glVertex3i(x, y + height, z + depth);
    glTexCoord2f(width / TEX_SCALE, height / TEX_SCALE);
    glVertex3i(x, y + height, z);
    glTexCoord2f(width / TEX_SCALE, 0);
    glVertex3i(x, y, z);
    glTexCoord2f(0, 0);
    glVertex3i(x, y, z + depth);

    // Top
    glTexCoord2f(0, height / TEX_SCALE);
    glVertex3i(x, y + height, z + depth);
    glTexCoord2f(width / TEX_SCALE, height / TEX_SCALE);
    glVertex3i(x + width, y + height, z + depth);
    glTexCoord2f(width / TEX_SCALE, 0);
    glVertex3i(x + width, y + height, z);
    glTexCoord2f(0, 0);
    glVertex3i(x, y + height, z);

    // Bottom
    glTexCoord2f(0, height / TEX_SCALE);
    glVertex3i(x, y, z + depth);
    glTexCoord2f(width / TEX_SCALE, height / TEX_SCALE);
    glVertex3i(x, y, z);
    glTexCoord2f(width / TEX_SCALE, 0);
    glVertex3i(x + width, y, z);
    glTexCoord2f(0, 0);
    glVertex3i(x + width, y, z + depth);

    glEnd();
}


void draw_skybox(Texture** skybox) {
    if (skybox == NULL)
        return;

    glPushAttrib(GL_ENABLE_BIT);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);

    // North
    if (skybox[0] != NULL && skybox[0]->available()) {
        skybox[0]->use();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3i(-4, 4, -4);
        glTexCoord2f(0, 1);
        glVertex3i(-4, -4, -4);
        glTexCoord2f(1, 1);
        glVertex3i(4, -4, -4);
        glTexCoord2f(1, 0);
        glVertex3i(4, 4, -4);
        glEnd();
    }

    // East
    if (skybox[1] != NULL && skybox[1]->available()) {
        skybox[1]->use();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3i(4, 4, -4);
        glTexCoord2f(0, 1);
        glVertex3i(4, -4, -4);
        glTexCoord2f(1, 1);
        glVertex3i(4, -4, 4);
        glTexCoord2f(1, 0);
        glVertex3i(4, 4, 4);
        glEnd();
    }

    // South
    if (skybox[2] != NULL && skybox[2]->available()) {
        skybox[2]->use();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3i(4, 4, 4);
        glTexCoord2f(0, 1);
        glVertex3i(4, -4, 4);
        glTexCoord2f(1, 1);
        glVertex3i(-4, -4, 4);
        glTexCoord2f(1, 0);
        glVertex3i(-4, 4, 4);
        glEnd();
    }

    // West
    if (skybox[3] != NULL && skybox[3]->available()) {
        skybox[3]->use();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3i(-4, 4, 4);
        glTexCoord2f(0, 1);
        glVertex3i(-4, -4, 4);
        glTexCoord2f(1, 1);
        glVertex3i(-4, -4, -4);
        glTexCoord2f(1, 0);
        glVertex3i(-4, 4, -4);
        glEnd();
    }

    // Top
    if (skybox[4] != NULL && skybox[4]->available()) {
        skybox[4]->use();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3i(4, 4, -4);
        glTexCoord2f(0, 1);
        glVertex3i(4, 4, 4);
        glTexCoord2f(1, 1);
        glVertex3i(-4, 4, 4);
        glTexCoord2f(1, 0);
        glVertex3i(-4, 4, -4);
        glEnd();
    }

    // Bottom
    if (skybox[5] != NULL && skybox[5]->available()) {
        skybox[5]->use();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3i(4, -4, 4);
        glTexCoord2f(0, 1);
        glVertex3i(4, -4, -4);
        glTexCoord2f(1, 1);
        glVertex3i(-4, -4, -4);
        glTexCoord2f(1, 0);
        glVertex3i(-4, -4, 4);
        glEnd();
    }

    glPopAttrib();
}

}} // SolidDescent::Renderer
