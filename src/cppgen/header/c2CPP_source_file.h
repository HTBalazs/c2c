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

#ifndef _CPPSOURCE_H_
#define _CPPSOURCE_H_

#include "c2CPP_header_file.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

namespace c2c {
    /** This class implements a generator for a C++ source file.
    */
	class c2CPP_source_file {
		c2CPP_header_file header;
	public:
		c2CPP_source_file(c2CPP_header_file const& hdr) : header{hdr} {}
		void write_file(std::string const& directory="") const;
	};
}

#endif //_CPPSOURCE_H_