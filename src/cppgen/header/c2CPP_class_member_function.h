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

#ifndef _CPPCLASSFUNCTION_H_
#define _CPPCLASSFUNCTION_H_

#include "c2CPP_class_member_type.h"
#include <vector>
#include <string>
#include <sstream>

namespace c2c {
	class c2CPP_class_member_function : public c2CPP_class_member_type  {
	protected:
		std::vector<c2CPP_declaration> arguments;
		std::string content;
		bool function_const = false;
		bool function_override = false;
	private:
		std::string get_argument_list() const;
	public:
		c2CPP_class_member_function(c2CPP_class_member_type const& mtype, std::vector<c2CPP_declaration> const& args, std::string const& con="", bool const& fc=false, bool const& ovr=false) : c2CPP_class_member_type{mtype}, arguments{args}, content{con}, function_const{fc}, function_override{ovr} {}
		c2CPP_class_member_function(std::string const& t, std::string const& n, bool const& c, std::string const& f="", std::vector<c2CPP_declaration> const& args=std::vector<c2CPP_declaration>{}, accessibility const& a=PRIVATE, std::string const& con="", bool const& fc=false, bool const& ovr=false) : c2CPP_class_member_type{t,n,c,f,"",a}, arguments{args}, content{con}, function_const{fc}, function_override{ovr} {}
		std::string get_declaration_code() const override;
		std::string get_definition_code(std::string const& class_name) const;
		void set_content(std::string const& c);
		friend std::stringstream& operator<<(std::stringstream& ss, c2CPP_class_member_function const& mf);
	};

	inline std::stringstream& operator<<(std::stringstream& ss, c2CPP_class_member_function const& mf) {
		ss << mf.get_declaration_code().c_str();
		return ss;
	}
}

#endif //_CPPCLASSFUNCTION_H_