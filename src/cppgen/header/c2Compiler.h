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

#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <string>
#include <vector>

namespace c2c {
	class c2Compiler {
	private:
        std::vector<std::string> flags;
        std::string incs;
        std::string libs;
        std::string compiler = "clang++";
		std::string name;
	public:
		c2Compiler(std::string const& n) : name{n} {}
        void set_compiler(std::string const& comp);
        void add_flag(std::string const& flag);
        void add_includes(std::string const& inc);
        void add_libraries(std::string const& lib);
		void compile() const;
	};
}

#endif //_COMPILER_H_