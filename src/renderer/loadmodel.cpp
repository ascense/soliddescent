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
    return NULL;
}

}} // SolidDescent::Renderer
