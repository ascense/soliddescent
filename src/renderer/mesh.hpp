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

#ifndef RENDERER_MESH_HPP
#define RENDERER_MESH_HPP

#include <string>
#include <cmath>
#include <GL/gl.h>

#include "../core/vector.hpp"
#include "../core/exceptions.hpp"


namespace SolidDescent { namespace Renderer {

struct Shader {
    std::string name;
    int index;
};


struct Vertex {
    Core::Vec3f pos;
    Core::Vec3f normal;
    float s, t;

    void normal_from_latlong(double lat, double lng);
};


class Mesh {
public:
    Mesh(std::string name);
    ~Mesh();

    void set_shader_count(int len);
    void set_index_count(int len);
    void set_vertex_count(int len);

    int get_shader_count();
    int get_index_count();
    int get_vertex_count();

    Shader** get_shaders();
    GLushort* get_indices();
    Vertex* get_vertex_array();

    const std::string name;

private:
    Shader **shaders;
    GLushort *indices;
    Vertex *vertices;

    int shaders_len;
    int indices_len;
    int vertices_len;
};

}} // SolidDescent::Renderer

#endif // RENDERER_MESH_HPP
