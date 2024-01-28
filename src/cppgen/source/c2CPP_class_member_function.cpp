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

void c2CPP_class_member_function::add_template_argument(c2CPP_declaration tmpl_arg) {
	template_arguments.push_back(tmpl_arg);
}

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
	std::string declaration = "";
	if(!template_arguments.empty()) {
		declaration += "template <";
	}
	for(auto const& it:template_arguments) {
		declaration += it.get_declaration_code()+",";
	}
	if(!template_arguments.empty()) {
		declaration.pop_back();
		declaration += "> ";
	}
	if(function_static) {
		declaration += "static "+c2CPP_declaration::get_declaration_code() + "(" + get_argument_list()+ ");";
	} else {
		declaration += c2CPP_declaration::get_declaration_code() + "(" + get_argument_list() + std::string{")"} + ((function_const)?" const":"") + ((function_override)?" override;":";");
	}
	return declaration;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the code definition of the function as the member of the given class.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_class_member_function::get_definition_code(std::string const& class_name) const {
	std::string definition = "";
	if(!template_arguments.empty()) {
		definition += "template <";
	}
	for(auto const& it:template_arguments) {
		definition += it.get_declaration_code()+",";
	}
	if(!template_arguments.empty()) {
		definition.pop_back();
		definition += "> ";
	}
	if(function_static) {
		definition += "/*static*/ " + std::string(function_inline?"inline ":"")+c2CPP_type::get_declaration_code() + " " + class_name + "::" + name + "(" + get_argument_list(false) + ")" + " {\n" + content + "\n}";
	} else {
		definition += std::string((function_inline&&template_arguments.empty())?"inline ":"")+c2CPP_type::get_declaration_code() + " " + class_name + "::" + name + "(" + get_argument_list(false) + ")" + ((function_const)?" const {\n":" {\n") + content + "\n}";
	}
	return definition;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Defines the content of the member function.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class_member_function::set_content(std::string const& c) {
	content = c;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns true if the function is const.
/////////////////////////////////////////////////////////////////////////////////////////
bool c2CPP_class_member_function::is_const() const {
	return function_const;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns true if the function is override.
/////////////////////////////////////////////////////////////////////////////////////////
bool c2CPP_class_member_function::is_override() const {
	return function_override;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns true if the function is static.
/////////////////////////////////////////////////////////////////////////////////////////
bool c2CPP_class_member_function::is_static() const {
	return function_static;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns true if the function is inline.
/////////////////////////////////////////////////////////////////////////////////////////
bool c2CPP_class_member_function::is_inline() const {
	return function_inline||!template_arguments.empty();
}
