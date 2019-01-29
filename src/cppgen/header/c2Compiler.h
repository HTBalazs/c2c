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

#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "c2Cmake_generator.h"
#include "c2CPP_header_file.h"
#include "c2CPP_source_file.h"
#include <string>
#include <vector>
#include <memory>

namespace c2c {
    /** This class wraps the runtime code assemly, compilation and linking.
    */
	class c2Compiler {
	private:
        std::string directory;
        std::string project_name;
        std::vector<std::shared_ptr<c2CPP_header_file>> headers;
        std::vector<std::shared_ptr<c2CPP_source_file>> sources;
        std::shared_ptr<c2Cmake_generator> cmake_generator;
    private:
        void generate_code() const;
        void generate_cmake_file() const;
    public:
        c2Compiler(std::string const& name) : project_name{name} {} 
        void set_directory(std::string const& dir);
        void set_project_name(std::string const& pn);
        void set_cmake_generator(std::shared_ptr<c2Cmake_generator> cmake_gen);
        void compile() const;
        void add_header(std::shared_ptr<c2CPP_header_file> hdr);
        void add_source(std::shared_ptr<c2CPP_source_file> src);
	};
}

#endif //_COMPILER_H_