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
    void set_triangle_count(int len);
    void set_vertex_count(int len);

    int get_shader_count();
    int get_triangle_count();
    int get_vertex_count();

    Shader** get_shaders();
    GLint* get_triangles();
    GLfloat* get_vertex_array();

    void put_vertex(Vertex* vert, int num);
    Vertex* get_vertex(int num);

    const std::string name;

    // Interleaved vertex array constants
    static const int vertexarray_size = 8;
    static const int vertexarray_vert_ofs = 0;
    static const int vertexarray_normal_ofs = 3;
    static const int vertexarray_texcoord_ofs = 6;

private:
    Shader **shaders;
    GLint *triangles;
    GLfloat *vertices;

    int shaders_len;
    int triangles_len;
    int vertices_len;
};

}} // SolidDescent::Renderer

#endif // RENDERER_MESH_HPP
