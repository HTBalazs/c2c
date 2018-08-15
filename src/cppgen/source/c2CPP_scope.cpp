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

#include "c2CPP_scope.h"

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Starts a scope.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_scope::open_session() const {
    return std::string(level, '\t') + type + " " + name + " {\n";
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Closes a scope.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_scope::close_session() const {
    return std::string(level, '\t') + "}";
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the anme of the scope.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_scope::get_name() const {
    return name;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Sets the level of the scope.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_scope::set_level(size_t const& lvl) {
    level = lvl;
}