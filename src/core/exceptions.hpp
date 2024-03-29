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

#ifndef CORE_EXCEPTIONS_HPP
#define CORE_EXCEPTIONS_HPP

#include <exception>


namespace SolidDescent { namespace Core {

class SolidDescentException : public std::exception {
public:
    SolidDescentException(const char* msg);

    const char* what();

private:
    const char* msg;
};


class CriticalError : public SolidDescentException {
public:
    CriticalError(const char* msg) : SolidDescentException(msg) {};
};

}} // SolidDescent::Core

#endif // CORE_EXCEPTIONS_HPP
