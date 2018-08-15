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

#include "c2CPP_namespace.h"

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Adds class to the namespace.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_namespace::add_class(c2CPP_class cl) {
	cl.set_level(level+1);
	classes.push_back(cl);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the vector of classes in the namespace.
/////////////////////////////////////////////////////////////////////////////////////////
std::vector<c2CPP_class> c2CPP_namespace::get_classes() const {
	return classes;
}