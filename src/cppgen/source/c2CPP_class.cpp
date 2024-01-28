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

#include "c2CPP_class.h"

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Starts the contruction of class definition.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_class::open_session() const {
	std::string osession = std::string(level, '\t') + type + " " + name;
	for(auto const& it:interface) {
		osession += std::string{it==interface[0] ? " : " : " , "} + "public " + it;
	}
	osession += " {\n";
	return osession;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Ends the construction of class definition.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_class::close_session() const {
	return std::string(level, '\t') + "};";
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add member type to the class. 
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class::add_member_type(c2CPP_class_member_type const& mtype) {
	member_types.push_back(mtype);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add member function to the class.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class::add_member_function(c2CPP_class_member_function const& mfunction) {
	member_functions.push_back(mfunction);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add member type to the class. 
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class::add_member_type(std::string const& type, std::string const& name, bool const& c/*=false*/, std::string const& f/*=""*/, std::string const& init/*=""*/, accessibility const& a/*=PRIVATE*/) {
	member_types.push_back(c2CPP_class_member_type{type, name, c, f, init, a});
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add member function to the class. 
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class::add_member_function(std::string const& type, std::string const& name, bool const& c, std::string const& f/*=""*/, std::vector<c2CPP_declaration> const& args/*=std::vector<c2CPP_declaration>{}*/, accessibility const& a/*=PRIVATE*/, std::string const& con/*=""*/, bool const& fc/*=false*/, bool const& ovr/*=false*/, bool const& inl/*=false*/) {
	member_functions.push_back(c2CPP_class_member_function{type, name, c, f, args, a, con, fc, ovr, false, inl});
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add static member function to the class. 
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class::add_static_member_function(std::string const& type, std::string const& name, bool const& c, std::string const& f/*=""*/, std::vector<c2CPP_declaration> const& args/*=std::vector<c2CPP_declaration>{}*/, accessibility const& a/*=PRIVATE*/, std::string const& con/*=""*/, bool const& inl/*=false*/) {
	member_functions.push_back(c2CPP_class_member_function{type, name, c, f, args, a, con, false, false, true, inl});
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add comment to the class. The comment will be shown in the generated code.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class::add_comment(std::string const& c) {
	comment = c;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add parent to the class (mandatory for dynamic linking).
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_class::add_interface(std::string const& parent) {
	interface.push_back(parent);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the member function with the given name
/////////////////////////////////////////////////////////////////////////////////////////
c2CPP_class_member_function& c2CPP_class::get_member_function(std::string const& n) {
	for(auto& it:member_functions) {
		if(it.get_name()==n) {
			return it;
		}
	}
	return member_functions[0];
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the vector of member functions. 
/////////////////////////////////////////////////////////////////////////////////////////
std::vector<c2CPP_class_member_function> c2CPP_class::get_member_functions() const {
	return member_functions;
}