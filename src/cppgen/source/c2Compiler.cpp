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

#include "c2Compiler.h"
#include "c2CPP_code_generator.h"
#include "prolog/pLogger.h"
#include <fstream>
#include <sstream>
#include <limits.h>
#include <unistd.h>

using namespace c2c;

std::string c2Compiler::current_directory() const {
  char result[1000];
  ssize_t count = readlink( "/proc/self/exe", result, 1000);
  return std::string( result, (count > 0) ? count : 0 );
}

void c2Compiler::generate_cmake_file() const {
	cmake_generator->set_directory(directory);
	cmake_generator->generate_cmake_file();
}

void c2Compiler::generate_code() const {
	c2CPP_code_generator code_gen;
	code_gen.set_directory(directory);
	for(auto const& it:headers) {
		code_gen.add_header(it);
	}
	for(auto const& it:sources) {
		code_gen.add_source(it);
	}
	code_gen.write_files();
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Compiles the code with cmake.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Compiler::compile() const {
	this->generate_code();
	this->generate_cmake_file();
	char pwd[1024];
	char *path = getcwd(pwd, sizeof(pwd));
	std::string wdir = std::string{pwd};
	std::string build_dir = wdir + "/" + directory;
	chdir(build_dir.c_str());
	ProLog::pLogger::logf<ProLog::NRM>("Generate Makefile with cmake...\n");
	fflush(stdout);
	system(std::string{"cmake ."}.c_str());
	ProLog::pLogger::logf<ProLog::NRM>("Run Makefile...\n");
	fflush(stdout);
	system("make");
	chdir(wdir.c_str());
}

void c2Compiler::set_directory(std::string const& dir) {
	directory = dir;
}

void c2Compiler::set_project_name(std::string const& pn) {
	project_name = pn;
}

void c2Compiler::set_cmake_generator(std::shared_ptr<c2Cmake_generator> cmake_gen) {
	cmake_generator = cmake_gen;
}

void c2Compiler::add_header(std::shared_ptr<c2CPP_header_file> hdr) {
	headers.push_back(hdr);
}
void c2Compiler::add_source(std::shared_ptr<c2CPP_source_file> src) {
	sources.push_back(src);
}

