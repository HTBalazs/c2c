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

#ifndef _CPPSCOPE_H_
#define _CPPSCOPE_H_

#include <string>

namespace c2c {
    class c2CPP_scope {
    protected:
        std::string type;
        std::string name;
        size_t level = 0;
        virtual std::string open_session() const;
        virtual std::string close_session() const;
    public:
        c2CPP_scope(std::string const& t, std::string const& n) : type{t}, name{n} {}
        std::string get_name() const;
        void set_level(size_t const& lvl);
    };
}

#endif //_CPPSCOPE_H_