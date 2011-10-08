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

#include "binaryio.hpp"


namespace SolidDescent { namespace Lib {


void* read_val(std::ifstream* stream, std::size_t len) {
    char* retval = new char[len];
    stream->read((char*) retval, len);

    return retval;
}


int read_int(std::ifstream* stream) {
    check_stream(stream);

    return *((int*) (read_val(stream, sizeof(int))));
}


float read_float(std::ifstream* stream) {
    check_stream(stream);

    return *((float*) (read_val(stream, sizeof(float))));
}


std::string read_cstr(std::ifstream* stream, int maxlen) {
    check_stream(stream);

    char* strbuf = new char[maxlen + 1];
    stream->read(strbuf, maxlen);
    strbuf[maxlen] = '\n';

    std::string str(strbuf);

    delete[] strbuf;

    return str;
}


Core::Vec3f read_vec3f(std::ifstream* stream) {
    check_stream(stream);

    Core::Vec3f vec;
    vec.x = *(float*) (read_val(stream, sizeof(float)));
    vec.y = *(float*) (read_val(stream, sizeof(float)));
    vec.z = *(float*) (read_val(stream, sizeof(float)));

    return vec;
}


void check_stream(std::ifstream* stream) {
    if (!stream->good())
        throw Core::SolidDescentException("Error reading binary data from file");
}

}} // SolidDescent::Lib
