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

#ifndef _CMAKE_GENERATOR_H_
#define _CMAKE_GENERATOR_H_

#include <string>
#include <vector>

namespace c2c {
    /** This class implements a generator for a CMakeLists.txt file.
    */
	class c2Cmake_generator {
    public:
        enum build_type {DEBUG, RELEASE};
    private:
        std::string directory;
        std::string cmake_version = "2.8.9";
        std::string project_name;
        build_type btype = RELEASE;
        std::string cxx_flags;
        std::string cxx_standard = "14";
        std::vector<std::string> link_dirs;
        std::vector<std::string> include_dirs;
        std::vector<std::string> dependencies;
    public:
        void set_directory(std::string const& dir);
        void set_cmake_version(std::string const& cmn);
        void set_project_name(std::string const& pn);
        void set_build_type(build_type const& tpye);
        void set_cxx_flags(std::string const& flags);
        void set_cxx_standard(std::string const& stnd);
        void add_link_dir(std::string const& ldir);
        void add_include_dir(std::string const& idir);
        void add_dependency(std::string const& dep);
        void generate_cmake_file() const;
	};
}

#endif //_CMAKE_GENERATOR_H_