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

#include "prolog/pLogger.h"
#include "c2Cmake_generator.h"
#include <fstream>
#include <sstream>
#include <limits.h>
#include <unistd.h>

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Set directory for the CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::set_directory(std::string const& dir) {
    directory = dir;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Set cmake_version for the CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::set_cmake_version(std::string const& cmn) {
    cmake_version = cmn;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Set project_name for the CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::set_project_name(std::string const& pn) {
    project_name = pn;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Set BUILD_TYPE for the CMakeLists.txt file (RELEASE or DEBUG).
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::set_build_type(build_type const& type) {
    btype = type;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Set CXX_FLAGS for the CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::set_cxx_flags(std::string const& flags) {
    cxx_flags = flags;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Set CXX_STANDARD for the CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::set_cxx_standard(std::string const& stnd) {
    cxx_standard = stnd;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add link directory for the CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::add_link_dir(std::string const& ldir) {
    link_dirs.push_back(ldir);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add include directory for the CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::add_include_dir(std::string const& idir) {
    include_dirs.push_back(idir);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add the paths of the dependencies for the CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::add_dependency(std::string const& dep) {
    dependencies.push_back(dep);
}

void c2Cmake_generator::add_include(std::string const& inc) {
    includes.push_back(inc);
}

void c2Cmake_generator::add_package(std::string const& pkg) {
    packages.push_back(pkg);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Generate CMakeLists.txt file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Cmake_generator::generate_cmake_file() const {
    ProLog::pLogger::logf<ProLog::NRM>("Generate CMakeLists.txt...\n");
    fflush(stdout);
    std::ofstream cmake_file;
    std::string file_name = directory + "/CMakeLists.txt";
    cmake_file.open(file_name.c_str(), std::ofstream::out);
    cmake_file  << "cmake_minimum_required(VERSION " << cmake_version << ")\n";
    cmake_file  << "project(" << project_name << ")\n\n";
    cmake_file  << "set(CMAKE_BUILD_TYPE " << (btype==RELEASE?"RELEASE":"DEBUG") << ")\n";
    cmake_file  << "set(CMAKE_CXX_STANDARD " << cxx_standard << ")\n";
    cmake_file  << "set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} \"" << cxx_flags << "\")\n";
    for(auto const& it:packages) {
        cmake_file << "find_package(" << it << ")\n";
    }
    for(auto const& it:link_dirs) {
        cmake_file << "link_directories(" << it << ")\n";
    }
    for(auto const& it:include_dirs) {
        cmake_file << "include_directories(" << it << ")\n";
    }
    for(auto const& it:includes) {
        cmake_file << "include(" << it << ")\n";
    }
    cmake_file  << "add_library(" << project_name << " SHARED " << project_name << ".cpp)\n";
    cmake_file  << "set_target_properties(" << project_name << " PROPERTIES SUFFIX \".so\")\n\n";
    for(auto const& it:dependencies) {
        cmake_file << "target_link_libraries(" << project_name << " " << it << ")\n";
    }
    cmake_file.close();
}


