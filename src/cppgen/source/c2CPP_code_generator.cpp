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

#include "c2CPP_code_generator.h"

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Set the directory for code generation.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_code_generator::set_directory(std::string const& dir) {
    directory = dir;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add header to the code generator.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_code_generator::add_header(std::shared_ptr<c2CPP_header_file> hdr) {
	headers.push_back(hdr);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add source to the code generator.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_code_generator::add_source(std::shared_ptr<c2CPP_source_file> src) {
	sources.push_back(src);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Writes header files.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_code_generator::write_header_files() const {
    for(auto const& it:headers) {
        it->write_file(directory);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Writes source files.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_code_generator::write_source_files() const {
    for(auto const& it:sources) {
        it->write_file(directory);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Writes header and source files.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_code_generator::write_files() const {
    if(directory!="") {
        system(std::string{"rm -r -f " + directory}.c_str());
        system(std::string{"mkdir " + directory}.c_str());
    }
    write_header_files();
    write_source_files();
}