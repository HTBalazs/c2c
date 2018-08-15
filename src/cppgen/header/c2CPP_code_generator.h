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

#ifndef _CPPCODEGENERATOR_H_
#define _CPPCODEGENERATOR_H_

#include "c2CPP_header_file.h"
#include "c2CPP_source_file.h"
#include <vector>
#include <string>

namespace c2c {
	class c2CPP_code_generator {
		std::vector<c2CPP_header_file> header;
		std::vector<c2CPP_source_file> source;
	public:
		c2CPP_code_generator() {}
		void add_header(c2CPP_header_file const& hdr);
		void add_source(c2CPP_source_file const& src);
        void write_header_files() const;
        void write_source_files() const;
		void write_files() const;
	};
}

#endif //_CPPCODEGENERATOR_H_