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

#ifndef _CPPTYPE_H_
#define _CPPTYPE_H_

#include <string>
#include <sstream>

namespace c2c {
    class c2CPP_type {
    protected:
        std::string type = "";
        bool constant = false;
        std::string form = "";
    public:
    	c2CPP_type(std::string const& t, bool const& c=false, std::string const& f="") : type{t}, constant{c}, form{f} {}
    	virtual std::string get_declaration_code() const;
    	friend std::stringstream& operator<<(std::stringstream& ss, c2CPP_type const& typ);
    };

    inline std::stringstream& operator<<(std::stringstream& ss, c2CPP_type const& typ) {
    	ss << typ.get_declaration_code().c_str();
    	return ss;
    }
}

#endif //_CPPTYPE_H_