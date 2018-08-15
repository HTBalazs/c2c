/*
    Copyright 2016-2018 Balazs Toth
    This file is part of Nauticle.

    Nauticle is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Nauticle is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Nauticle.  If not, see <http://www.gnu.org/licenses/>.

    For more information please visit: https://bitbucket.org/nauticleproject/
*/

#include "c2CPP_declaration.h"

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the declaration code.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_declaration::get_declaration_code() const {
    std::string code = c2CPP_type::get_declaration_code() + " " + name + (init_value==""?"":(" = " + init_value));
	return code;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the name of the type.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_declaration::get_name() const {
    return name;
}