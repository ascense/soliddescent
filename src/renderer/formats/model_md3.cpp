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

#include "modelfmt.hpp"

// MD3-Specific Magic Numbers
#define MD3_IDENT 0x33504449
#define MD3_MAX_QPATH 64


namespace SolidDescent { namespace Renderer {

ModelData* load_md3(std::ifstream* stream) {
    ModelData* md3 = NULL;

    struct MD3Header {
        int32_t magic;
        int32_t version;
        char name[MD3_MAX_QPATH];
        int32_t flags;

        int32_t num_frames;
        int32_t num_tags;
        int32_t num_surfaces;
        int32_t num_skins;

        int32_t ofs_frames;
        int32_t ofs_tags;
        int32_t ofs_surfaces;
    } __attribute__((packed)) header;

    try {
        /** HEADER **/
        stream->read((char*) &header, sizeof(header));

        // Check header "magic number"
        if (header.magic != MD3_IDENT)
            return NULL;

        md3 = new ModelData(std::string(header.name));
        md3->set_frame_count(header.num_frames);
        md3->set_tag_count(header.num_tags);
        md3->set_mesh_count(header.num_surfaces);

        /** FRAMES **/
        stream->seekg(header.ofs_frames);

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
        stream->seekg(header.ofs_tags);

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
        long ofs_surface = header.ofs_surfaces;

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
                surf->shaders[j] = shader;

                shader->name = Lib::read_cstr(stream, MD3_MAX_QPATH);
                shader->index = Lib::read_int(stream);

                shader->tex = new Texture(shader->name, &TEX_RGB);
            }

            /** TRIANGLES **/
            stream->seekg(ofs_surface + ofs_triangles);

            for (int j = 0; j < surf->get_index_count(); ++j)
                surf->indices[j] = (unsigned int) (Lib::read_int(stream));

            /** VERTICES (XYZNormal) **/
            stream->seekg(ofs_surface + ofs_vertices);

            Vertex* vert;
            short x, y, z;
            for (int j = 0; j < surf->get_vertex_count(); ++j) {
                vert = &surf->vertices[j];

                Lib::read_val(stream, &x, 2);
                Lib::read_val(stream, &y, 2);
                Lib::read_val(stream, &z, 2);

                // Convert to opengl-space by swapping z and y axes
                vert->pos.x = x;
                vert->pos.z = y;
                vert->pos.y = z;

                // Scale back vertex coordinates by a factor of 1 / 64
                vert->pos.scale(1.0f / 64);

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
                surf->vertices[j].s = Lib::read_float(stream);
                surf->vertices[j].t = 1.0f - Lib::read_float(stream);
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
