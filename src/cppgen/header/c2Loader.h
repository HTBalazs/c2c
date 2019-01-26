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

#ifndef _LOADER_H_
#define _LOADER_H_

#include "c2Interface.h"
#include <string>
#include "dlfcn.h"

namespace c2c {
	class c2Loader {
	    typedef c2Interface* create_t();
	    typedef void destroy_t(c2Interface*);
	private:
		std::string name;
		void* handle;
		destroy_t* destroy;
		create_t* create;
	public:
		c2Loader(std::string const& dir, std::string const& n);
		c2Interface* create_object();
		void destroy_object(c2Interface* obj);
	};
}

#endif //_LOADER_H_