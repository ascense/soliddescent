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

#include "loadmodel.hpp"


namespace SolidDescent { namespace Renderer {

Model* load_model(std::string path, ModelFmt fmt) {
    Model* mod;
    std::ifstream stream;

    stream.open(path.c_str(), std::ios::binary);
    if (!stream.good()) {
        stream.close();
        return NULL;
    }

    switch (fmt) {
        case MOD_MD3:
            mod = load_md3(&stream);
            break;

        default:
            mod = NULL;
            break;
    }

    stream.close();

    return mod;
}


Model* load_md3(std::ifstream* stream) {
    Model* md3 = NULL;

    try {
        /** HEADER **/
        // Check header "magic number"
        if (Lib::read_int(stream) != MD3_IDENT)
            return NULL;

        // Ignore md3 version number
        stream->seekg(4, std::ios::cur);

        // Read model name
        md3 = new Model(Lib::read_cstr(stream, MD3_MAX_QPATH));
        if (!md3)
            return NULL;

        // Ignore md3 flags
        stream->seekg(4, std::ios::cur);

        // The real "meat" of the header :)
        md3->set_frame_count(Lib::read_int(stream));
        md3->set_tag_count(Lib::read_int(stream));
        md3->set_mesh_count(Lib::read_int(stream));

        // Ignore skin count
        stream->seekg(4, std::ios::cur);

        int ofs_frames = Lib::read_int(stream);
        int ofs_tags = Lib::read_int(stream);
        int ofs_surfaces = Lib::read_int(stream);

        /** FRAMES **/
        stream->seekg(ofs_frames);

        for (int i = 0; i < md3->get_frame_count(); ++i) {
            ModelFrame *frame = new ModelFrame();
            md3->get_frames()[i] = frame;

            frame->bounds_min = Lib::read_vec3f(stream);
            frame->bounds_max = Lib::read_vec3f(stream);
            frame->local_orig = Lib::read_vec3f(stream);
            frame->radius = Lib::read_float(stream);
            frame->name = Lib::read_cstr(stream, MD3_MAX_QPATH);
        }

        /** TAGS **/
        stream->seekg(ofs_tags);

        for (int i = 0; i < md3->get_tag_count(); ++i) {
            ModelTag *tag = new ModelTag();
            md3->get_tags()[i] = tag;

            tag->name = Lib::read_cstr(stream, MD3_MAX_QPATH);
            tag->origin = Lib::read_vec3f(stream);
            tag->x_axis = Lib::read_vec3f(stream);
            tag->y_axis = Lib::read_vec3f(stream);
            tag->z_axis = Lib::read_vec3f(stream);
        }

        /** SURFACES **/
        long ofs_surface = ofs_surfaces;

        for (int i = 0; i < md3->get_mesh_count(); ++i) {
            stream->seekg(ofs_surface);

            // Check surface "magic number"
            if (Lib::read_int(stream) != MD3_IDENT)
                throw Core::SolidDescentException("Mesh data of unknown format");

            Mesh* surf = new Mesh(Lib::read_cstr(stream, MD3_MAX_QPATH));
            md3->get_meshes()[i] = surf;

            // Ignore surface flags
            stream->seekg(4, std::ios::cur);

            // Verify that the mesh frame count maches the model frame count
            if (Lib::read_int(stream) != md3->get_frame_count())
                throw Core::SolidDescentException("Mesh and model frame counts do not match");

            // Surface "header" data
            surf->set_shader_count(Lib::read_int(stream));
            surf->set_vertex_count(Lib::read_int(stream));
            surf->set_index_count(Lib::read_int(stream) * 3);

            int ofs_triangles = Lib::read_int(stream);
            int ofs_shaders = Lib::read_int(stream);
            int ofs_texcoords = Lib::read_int(stream);
            int ofs_vertices = Lib::read_int(stream);
            int ofs_end = Lib::read_int(stream);

            /** SHADERS **/
            stream->seekg(ofs_surface + ofs_shaders);

            for (int j = 0; j < surf->get_shader_count(); ++j) {
                Shader* shader = new Shader();
                surf->get_shaders()[j] = shader;

                shader->name = Lib::read_cstr(stream, MD3_MAX_QPATH);
                shader->index = Lib::read_int(stream);
            }

            /** TRIANGLES **/
            stream->seekg(ofs_surface + ofs_triangles);

            for (int j = 0; j < surf->get_index_count(); ++j)
                surf->get_indices()[j] = (unsigned int) (Lib::read_int(stream));

            /** VERTICES (XYZNormal) **/
            stream->seekg(ofs_surface + ofs_vertices);

            Vertex* vert;			short x, y, z;			for (int j = 0; j < surf->get_vertex_count(); ++j) {
                vert = &surf->get_vertex_array()[j];				Lib::read_val(stream, &x, 2);
                Lib::read_val(stream, &y, 2);
                Lib::read_val(stream, &z, 2);				// Convert to opengl-space by swapping z and y axes
                vert->pos.x = x;
                vert->pos.z = y;
                vert->pos.y = z;
                // Scale back vertex coordinates by a factor of 1 / 64				vert->pos.scale(1.0f / 64);

                char lat, lng;
                stream->read(&lat, 1);
                stream->read(&lng, 1);

                vert->normal_from_latlong(
                    (double) (lat * (2 * M_PI) / 255),
                    (double) (lng * (2 * M_PI) / 255)
                );
            }

            /** TEXTURE-COORDS (ST) **/
            stream->seekg(ofs_surface + ofs_texcoords);

            for (int j = 0; j < surf->get_vertex_count(); ++j) {
                surf->get_vertex_array()[j].s = Lib::read_float(stream);
                surf->get_vertex_array()[j].t = Lib::read_float(stream);
            }

            // Calculate offset to next surface
            ofs_surface += ofs_end;
        }

    } catch (Core::SolidDescentException& e) {
        if (md3)
            delete md3;
        // TODO: Log error message

        return NULL;
    }

    return md3;
}

}} // SolidDescent::Renderer
