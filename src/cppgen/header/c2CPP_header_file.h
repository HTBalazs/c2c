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

#ifndef _CPPHEADER_H_
#define _CPPHEADER_H_

#include "c2CPP_namespace.h"
#include <string>
#include <vector>
#include <fstream>

namespace c2c{
	class c2CPP_header_file {
		std::string name = "";
		std::vector<c2CPP_namespace> ns;
		std::vector<std::string> inc_hdr;
		std::vector<std::string> inc_lib;
	private:
		std::string intro() const;
		std::string generate_guard_name() const;
		std::string include_guard_begin() const;
		std::string include_guard_end() const;
		std::string include_file(std::string const& file_name) const;
		std::string include_lib_file(std::string const& file_name) const;
	public:
		c2CPP_header_file() {}
		c2CPP_header_file(std::string const& n) : name{n} {}
		void add_include(std::string const& hdr, bool lib=false);
		void add_namespace(std::string const& nsname);
		c2CPP_namespace& get_namespace(std::string const& nsname);
		std::vector<c2CPP_namespace> get_namespaces() const;
		void write_file() const;
		std::string get_name() const;
	};
}

#endif //_CPPHEADER_H_