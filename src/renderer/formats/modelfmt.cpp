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


namespace SolidDescent { namespace Renderer {

ModelData* load_model(std::string path) {
    // Determine format
    ModelSrcFmt fmt;

    size_t ext_start = path.length() - 3;
    if (ext_start <= 0)
        throw Core::SolidDescentException("Failed to determine model format");

    if (path.compare(ext_start, 3, "md3") == 0)
        fmt = MOD_MD3;
    else
        fmt = MOD_UNSUPPORTED;

    return load_model(path.c_str(), fmt);
}


ModelData* load_model(const char* path, ModelSrcFmt fmt) {
    ModelData *data;
    std::ifstream stream;

    stream.open(path, std::ios::binary);
    if (!stream.good()) {
        stream.close();
        throw Core::SolidDescentException("Could not read model file");
    }

    try {
        switch (fmt) {
            case MOD_MD3:
                data = load_md3(&stream);
                break;

            default:
                throw Core::SolidDescentException("Unsupported model format");
        }
    } catch (std::exception &e) {
        stream.close();
        throw;
    }

    stream.close();

    if (!data)
        throw Core::SolidDescentException("Failed to load model data");

    return data;
}

}} // SolidDescent::Renderer
