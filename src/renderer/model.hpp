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

#ifndef RENDERER_MODEL_HPP
#define RENDERER_MODEL_HPP

#include <string>

#include "mesh.hpp"
#include "../core/vector.hpp"
#include "../core/exceptions.hpp"


namespace SolidDescent { namespace Renderer {

struct ModelTag {
    std::string name;

    Core::Vec3f origin;
    Core::Vec3f x_axis;
    Core::Vec3f y_axis;
    Core::Vec3f z_axis;
};


struct ModelFrame {
    std::string name;

    float radius;
    Core::Vec3f bounds_min;
    Core::Vec3f bounds_max;
    Core::Vec3f local_orig;
};


class Model {
public:
    Model(std::string name);
    ~Model();

    void set_frame_count(int len);
    void set_tag_count(int len);
    void set_mesh_count(int len);

    int get_frame_count();
    int get_tag_count();
    int get_mesh_count();

    ModelFrame** get_frames();
    ModelTag** get_tags();
    Mesh** get_meshes();

    const std::string name;

private:
    ModelFrame** frames;
    ModelTag** tags;
    Mesh** meshes;

    int frames_len;
    int tags_len;
    int meshes_len;
};

}} // SolidDescent::Renderer

#endif // RENDERER_MODEL_HPP
