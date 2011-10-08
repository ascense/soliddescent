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

#include "mesh.hpp"


namespace SolidDescent { namespace Renderer {

void Vertex::normal_from_latlong(double lat, double lng) {
    this->normal.x = (float) (std::cos(lat) * std::sin(lng));
    this->normal.y = (float) (std::cos(lng));
    this->normal.z = (float) (std::sin(lat) * std::sin(lng));
}


Mesh::Mesh(std::string name) : name(name), shaders(NULL), triangles(NULL), vertices(NULL) {}


Mesh::~Mesh() {
    if (shaders) {
        for (int i = 0; i < shaders_len; ++i) {
            if (shaders[i])
                delete shaders[i];
        }
        delete shaders;
    }

    if (vertices) {
        for (int i = 0; i < vertices_len; ++i) {
            if (vertices[i])
                delete vertices[i];
        }
        delete vertices;
    }

    if (triangles)
        delete [] triangles;
}


void Mesh::set_shader_count(int len) {
    if (shaders != NULL)
        throw Core::SolidDescentException("Cannot change the number of shaders for a mesh");

    shaders = new Shader*[len]();
    shaders_len = len;
}


void Mesh::set_triangle_count(int len) {
    if (triangles != NULL)
        throw Core::SolidDescentException("Cannot change the number of triangles for a mesh");

    triangles = new int[len];
    triangles_len = len;
}


void Mesh::set_vertex_count(int len) {
    if (vertices != NULL)
        throw Core::SolidDescentException("Cannot change the number of vertices for a mesh");

    vertices = new Vertex*[len]();
    vertices_len = len;
}


int Mesh::get_shader_count() {
    if (shaders == NULL)
        return -1;

    return shaders_len;
}


int Mesh::get_triangle_count() {
    if (triangles == NULL)
        return -1;

    return triangles_len;
}


int Mesh::get_vertex_count() {
    if (vertices == NULL)
        return -1;

    return vertices_len;
}


Shader** Mesh::get_shaders() {
    return shaders;
}


int* Mesh::get_triangles() {
    return triangles;
}


Vertex** Mesh::get_vertices() {
    return vertices;
}

}} // SolidDescent::Renderer
