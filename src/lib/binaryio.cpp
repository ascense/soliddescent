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

int read_int(std::ifstream* stream) {
    if (!stream->good())
        throw Core::SolidDescentException("Error reading binary data");

    int retval;
    stream->read((char*) &retval, 4);

    if (stream->fail())
        throw Core::SolidDescentException("Error reading binary data");

    return retval;
}

}} // SolidDescent::Lib
