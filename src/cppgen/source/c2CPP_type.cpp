/*
    Copyright 2016-2019 Balazs Toth
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

#include "c2CPP_type.h"

using namespace c2c;

void c2CPP_type::set_type(std::string const& t) {
    type = t;
}

void c2CPP_type::set_constant(bool const& c) {
    constant = c;
}

void c2CPP_type::set_form(std::string const& f) {
    form = f;
}


std::string const& c2CPP_type::get_type() const {
    return type;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the declaration code of the type.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_type::get_declaration_code(bool const& print_init/*=true*/) const {
    std::string code = type + (constant?" const":"") + form;
	return code;
}