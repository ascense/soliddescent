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

#include "logging.hpp"


namespace SolidDescent { namespace Lib {

void log_error(Core::SolidDescentException* e) {
    std::cout << "Error: " << e->what() << std::endl;
}


void log_error(Core::SolidDescentException* e, std::string source) {
    std::cout << source << ": ";
    log_error(e);
}

}} // SolidDescent::Lib
