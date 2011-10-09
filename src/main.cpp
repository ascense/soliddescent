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

#include <iostream>

#include "soliddescent.hpp"


int main(int argc, char *argv[]) {
    SolidDescent::Core::Engine *engine = NULL;
    int ecode = 0;

    try {
        engine = new SolidDescent::Core::Engine();
        engine->run();
    } catch (SolidDescent::Core::CriticalError& e) {
        std::cout << "Critical Error!" << std::endl;
        std::cout << e.what() << std::endl;
        ecode = 7;
    } catch (SolidDescent::Core::SolidDescentException& e) {
        std::cout << "Internal Error!" << std::endl;
        std::cout << e.what() << std::endl;
        ecode = 5;
    }

    if (engine)
        delete engine;

    return ecode;
}
