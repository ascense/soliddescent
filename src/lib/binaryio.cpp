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


void read_val(std::ifstream* stream, void* val, std::size_t len) {
    stream->read((char*) val, len);
}


int read_int(std::ifstream* stream) {
    check_stream(stream);

    int ret;
    read_val(stream, &ret, sizeof(int));

    return ret;
}


float read_float(std::ifstream* stream) {
    check_stream(stream);

    float ret;
    read_val(stream, &ret, sizeof(float));

    return ret;
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
    float val;

    read_val(stream, &val, sizeof(float));
    vec.x = val;
    read_val(stream, &val, sizeof(float));
    vec.y = val;
    read_val(stream, &val, sizeof(float));
    vec.z = val;

    return vec;
}


void check_stream(std::ifstream* stream) {
    if (!stream->good())
        throw Core::SolidDescentException("Error reading binary data from file");
}

}} // SolidDescent::Lib
