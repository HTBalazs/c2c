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

#include "c2CPP_class_member_function.h"

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the argument list of the function.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_class_member_function::get_argument_list(bool const& print_init/*=true*/) const {
	std::string argument_list = "";
	for(auto const& it:arguments) {
		argument_list += it.get_declaration_code(print_init);
		if(&it!=&arguments.back()) {
			argument_list += ", ";
		}
	}
	return argument_list;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the declaration code of the function.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_class_member_function::get_declaration_code(bool const& print_init/*=true*/) const {
	std::string declaration = c2CPP_declaration::get_declaration_code() + "(" + get_argument_list() + std::string{")"} + ((function_const)?" const":"") + ((function_override)?" override;":";");
	return declaration;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the code definition of the function as the member of the given class.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_class_member_function::get_definition_code(std::string const& class_name) const {
	std::string definition = c2CPP_type::get_declaration_code() + " " + class_name + "::" + name + "(" + get_argument_list(false) + ")" + ((function_const)?" const {\n":" {\n") + content + "\n}";
	return definition;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Defines the content of the member function.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class_member_function::set_content(std::string const& c) {
	content = c;
}