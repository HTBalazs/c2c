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

#ifndef _CPPCLASSTYPE_H_
#define _CPPCLASSTYPE_H_

#include "c2CPP_type.h"
#include <string>
#include <sstream>

namespace c2c {
    class c2CPP_declaration : public c2CPP_type {
    protected:
        std::string name;
        std::string init_value = "";
    public:
        c2CPP_declaration(c2CPP_type const& typ, std::string const& n, std::string const& init="") : c2CPP_type{typ}, name{n}, init_value{init} {}
    	c2CPP_declaration(std::string const& t, std::string const& n, bool const& c=false, std::string const& f="", std::string const& init="") : c2CPP_type{t,c,f}, name{n}, init_value{init} {}
        std::string get_name() const;
    	virtual std::string get_declaration_code(bool const& print_init=true) const override;
    	friend std::stringstream& operator<<(std::stringstream& ss, c2CPP_declaration const& typ);
    };

    inline std::stringstream& operator<<(std::stringstream& ss, c2CPP_declaration const& typ) {
    	ss << typ.get_declaration_code().c_str();
    	return ss;
    }
}

#endif //_CPPCLASSTYPE_H_