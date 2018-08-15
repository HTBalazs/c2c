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

#include "c2Loader.h"
#include <iostream>

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Constructor.
/////////////////////////////////////////////////////////////////////////////////////////
c2Loader::c2Loader(std::string const& n) : name{n} {
	handle = dlopen(("./lib" + name + ".so").c_str(), RTLD_NOW);
	if(!handle) {
		printf("The error is %s", dlerror());
	}
    create = (create_t*)dlsym(handle,"create");
    destroy = (destroy_t*)dlsym(handle,"destroy");
	if(!create) {
	      std::cout<<"The error is %s"<<dlerror();
	}
	if(!destroy) {
	      std::cout<<"The error is %s"<<dlerror();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Creates and returns a new object instantiated from the dynamic library.
/////////////////////////////////////////////////////////////////////////////////////////
c2Interface* c2Loader::create_object() {
	return create();
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Destroys the given object.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Loader::destroy_object(c2Interface* obj) {
	destroy(obj);
}