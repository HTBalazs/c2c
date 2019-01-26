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

#include "prolog/pLogger.h"
#include "c2Compiler.h"
#include <fstream>
#include <sstream>
#include <limits.h>
#include <unistd.h>

using namespace c2c;

// std::string c2Compiler::current_directory() const {
//     char buffer[1000];
//     GetModuleFileName(NULL, buffer, 1000);
//     string::size_type pos = string(buffer).find_last_of("\\/");
//     return string(buffer).substr(0, pos);
// }

std::string c2Compiler::current_directory() const {
  char result[1000];
  ssize_t count = readlink( "/proc/self/exe", result, 1000);
  return std::string( result, (count > 0) ? count : 0 );
}

void c2Compiler::generate_cmake_file() const {
    std::ofstream cmake_file;
    std::string file_name = directory + "/" + cmake_name;
    cmake_file.open(file_name.c_str(), std::ofstream::out);
    cmake_file  << "cmake_minimum_required(VERSION 2.8.9)\n";
    cmake_file  << "set(CMAKE_CXX_STANDARD 14)\n";
    cmake_file  << "set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} \"-pthread -O3 -fPIC\")\n";
    cmake_file  << "project(pmBinary_case)\n\n";
    cmake_file  << "link_directories(/usr/local/lib/prolog)\n";
    cmake_file  << "link_directories(/usr/local/lib/commonutils)\n";
    cmake_file  << "link_directories(/usr/local/lib/c2c)\n";
    cmake_file  << "link_directories(/usr/local/lib/nauticle)\n\n";
    cmake_file  << "include_directories(/usr/local/include/nauticle)\n";
    cmake_file  << "include_directories(/usr/local/include/prolog)\n";
    cmake_file  << "include_directories(/usr/local/include/c2c)\n";
    cmake_file  << "include_directories(/usr/local/include/commonutils)\n\n";
    cmake_file  << "add_library(pmBinary_case SHARED pmBinary_case.cpp)\n";
    cmake_file  << "set_target_properties(pmBinary_case PROPERTIES SUFFIX \".so\")\n\n";
    cmake_file  << "#Bring dependencies\n";
    cmake_file  << "target_link_libraries(pmBinary_case /usr/local/lib/prolog/libprolog.a)\n";
    cmake_file  << "target_link_libraries(pmBinary_case /usr/local/lib/commonutils/libcommonutils.a)\n";
    cmake_file  << "target_link_libraries(pmBinary_case /usr/local/lib/libyaml-cpp.a)\n";
    cmake_file  << "target_link_libraries(pmBinary_case /usr/local/lib/c2c/libc2c.a)\n";
    cmake_file  << "target_link_libraries(pmBinary_case /usr/local/lib/nauticle/libnauticle.a)\n\n";
    cmake_file  << "install(TARGETS pmBinary_case LIBRARY DESTINATION . PUBLIC_HEADER DESTINATION .)\n";
    cmake_file.close();
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Compiles the code with cmake.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Compiler::compile() const {
    char pwd[1024];
    char *path = getcwd(pwd, sizeof(pwd));
    std::string wdir = std::string{pwd};
    std::string build_dir = wdir + "/" + directory;
    chdir(build_dir.c_str());
    system(std::string{"cmake ."}.c_str());
    system(std::string{"cmake ."}.c_str());
    system("make");
    chdir(wdir.c_str());
}

void c2Compiler::set_directory(std::string const& dir) {
    directory = dir;
}

void c2Compiler::set_project_name(std::string const& pn) {
    project_name = pn;
}

void c2Compiler::set_cmake_name(std::string const& cmn) {
    cmake_name = cmn;
}

