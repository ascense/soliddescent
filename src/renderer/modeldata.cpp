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

#include "modeldata.hpp"


namespace SolidDescent { namespace Renderer {

ModelData::ModelData(std::string name)
        : name(name), frames(NULL), tags(NULL), meshes(NULL) {}


ModelData::~ModelData() {
    if (frames) {
        for (int i = 0; i < frames_len; ++i) {
            if (frames[i])
                delete frames[i];
        }
        delete [] frames;
    }

    if (tags) {
        for (int i = 0; i < tags_len; ++i) {
            if (tags[i])
                delete tags[i];
        }
        delete [] tags;
    }

    if (meshes) {
        for (int i = 0; i < meshes_len; ++i) {
            if (meshes[i])
                delete meshes[i];
        }
        delete [] meshes;
    }
}


void ModelData::set_frame_count(int len) {
    if (frames != NULL)
        throw Core::SolidDescentException("Cannot change the number of frames for a model");

    frames = new ModelFrame*[len]();
    frames_len = len;
}


void ModelData::set_tag_count(int len) {
    if (tags != NULL)
        throw Core::SolidDescentException("Cannot change the number of tags for a model");

    tags = new ModelTag*[len]();
    tags_len = len;
}


void ModelData::set_mesh_count(int len) {
    if (meshes != NULL)
        throw Core::SolidDescentException("Cannot change the number of meshes for a model");

    meshes = new Mesh*[len]();
    meshes_len = len;
}


int ModelData::get_frame_count() {
    if (frames == NULL)
        return -1;

    return frames_len;
}


int ModelData::get_tag_count() {
    if (tags == NULL)
        return -1;

    return tags_len;
}


int ModelData::get_mesh_count() {
    if (meshes == NULL)
        return -1;

    return meshes_len;
}


ModelFrame** ModelData::get_frames() {
    return frames;
}


ModelTag** ModelData::get_tags() {
    return tags;
}


Mesh** ModelData::get_meshes() {
    return meshes;
}

}} // SolidDescent::Renderer

