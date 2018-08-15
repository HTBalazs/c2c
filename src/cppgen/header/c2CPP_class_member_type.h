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

#ifndef _CPPMEMBER_H_
#define _CPPMEMBER_H_

#include "c2CPP_declaration.h"
#include <string>

namespace c2c {
	enum accessibility {PRIVATE, PROTECTED, PUBLIC};
	
	class c2CPP_class_member_type : public c2CPP_declaration {
	protected:
		accessibility access = PRIVATE;
	public:
		c2CPP_class_member_type(c2CPP_declaration const& decl, accessibility const& a=PRIVATE) : c2CPP_declaration{decl}, access{a} {}
		c2CPP_class_member_type(std::string const& t, std::string const& n, bool const& c=false, std::string const& f="", std::string const& init="", accessibility const& a=PRIVATE) : c2CPP_declaration{t,n,c,f,init}, access{a} {}
		accessibility get_accessibility() const;
		friend std::stringstream& operator<<(std::stringstream& ss, c2CPP_class_member_type const& typ);
	};

	inline std::stringstream& operator<<(std::stringstream& ss, c2CPP_class_member_type const& typ) {
    	ss << typ.get_declaration_code().c_str();
    	return ss;
    }
}

#endif //_CPPMEMBER_H_