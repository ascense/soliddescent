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

#ifndef CORE_RESOURCE_HPP
#define CORE_RESOURCE_HPP

#include <string>

#include "exceptions.hpp"


namespace SolidDescent { namespace Core {

class Resource {
public:
    Resource(std::string path) : path(path), available(true) {};

    bool is_available() {return available;};

    virtual void load() throw (SolidDescentException) = 0;
    virtual void unload() = 0;

protected:
    std::string path;
    bool available;
};

}} // SolidDescent::Core

#endif // CORE_RESOURCE_HPP
