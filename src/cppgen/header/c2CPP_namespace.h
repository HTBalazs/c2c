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

#ifndef _CPPNAMESPACE_H_
#define _CPPNAMESPACE_H_

#include "c2CPP_scope.h"
#include "c2CPP_declaration.h"
#include "c2CPP_class.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>

namespace c2c {
	class c2CPP_namespace : public c2CPP_scope {
		std::vector<c2CPP_declaration> types;
		std::vector<c2CPP_class> classes;
	public:
		c2CPP_namespace(std::string const& n) : c2CPP_scope{"namespace", n} {}
		void add_class(c2CPP_class cl);
		void add_definition(c2CPP_declaration tp);
		std::vector<c2CPP_class> const& get_classes() const;
		std::vector<c2CPP_declaration> const& get_definitions() const;
		friend std::stringstream& operator<<(std::stringstream& ss, c2CPP_namespace const& ns);
	};
	
	inline std::stringstream& operator<<(std::stringstream& ss, c2CPP_namespace const& ns) {
		ss << ns.open_session().c_str();
		for(auto const& it:ns.types) {
			ss << "\t";
			ss << it << "\n";
		}
		ss << "\n";
		for(auto const& it:ns.classes) {
			ss << it << "\n";
		}
		for(auto const& it_cl:ns.classes) {
			for(auto const& it_mf:it_cl.get_member_functions()) {
				if(it_mf.is_inline()) {
					ss << "\n\t";
					std::regex pattern("\n");
					ss << std::regex_replace(it_mf.get_definition_code(it_cl.get_name()),pattern,"\n\t").c_str() << std::endl;
				}
			}
		}
		ss << ns.close_session().c_str() << "\n";
		return ss;
	}
}


#endif //_CPPNAMESPACE_H_