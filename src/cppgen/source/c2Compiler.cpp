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

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Compiles the code
/////////////////////////////////////////////////////////////////////////////////////////
void c2Compiler::compile() const {
	std::string cpp2object = compiler;
	std::string object2shared = compiler;
	for(auto const& it:flags) {
		cpp2object += " " + it;
		object2shared += " " + it;
	}
	cpp2object += " -c " + name + ".cpp -o " + name + ".o";
	object2shared += " -shared " + name + ".o -o lib" + name + ".so";
	system(cpp2object.c_str());
	system(object2shared.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Set the compiler.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Compiler::set_compiler(std::string const& comp) {
	compiler = comp;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Add flag the compilation.
/////////////////////////////////////////////////////////////////////////////////////////
void c2Compiler::add_flag(std::string const& flag) {
	flags.push_back(flag);
}