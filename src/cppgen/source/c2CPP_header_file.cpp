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

#include "c2CPP_header_file.h"
#include "prolog/pLogger.h"
#include <ctime>
#include <chrono>

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the information of the header file.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_header_file::intro() const {
	std::string message = "// This file is automatically generated by the c2c code generator on ";
	std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	message += std::ctime(&current_time);
	return message;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Generates include guard name based on the header name.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_header_file::generate_guard_name() const {
	std::string uppername = name;
	std::transform(uppername.begin(), uppername.end(), uppername.begin(), toupper);
	return "_" + uppername + "_H_";
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the include guard start.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_header_file::include_guard_begin() const {
	return "#ifndef " + generate_guard_name() + "\n" + "#define " + generate_guard_name();
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the include guard end.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_header_file::include_guard_end() const {
	return "#endif //" + generate_guard_name();
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the code of including a header file.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_header_file::include_file(std::string const& file_name) const {
	return "#include \"" + file_name + "\"";
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the code of including a header file.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_header_file::include_lib_file(std::string const& file_name) const {
	return "#include <" + file_name + ">";
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Adds header to be included. Path without "" or <> has to be given.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_header_file::add_include(std::string const& hdr, bool lib/*=false*/) {
	if(lib) {
		inc_lib.push_back(hdr);
	} else {
		inc_hdr.push_back(hdr);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Adds a namespace to the header file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_header_file::add_namespace(std::string const& nsname) {
	ns.push_back(c2CPP_namespace{nsname});
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the namespace with the given name.
/////////////////////////////////////////////////////////////////////////////////////////
c2CPP_namespace& c2CPP_header_file::get_namespace(std::string const& nsname) {
	for(auto& it:ns) {
		if(it.get_name()==nsname) {
			return it;
		}
	}
	return ns[0];
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the vector of the namespaces.
/////////////////////////////////////////////////////////////////////////////////////////
std::vector<c2CPP_namespace> c2CPP_header_file::get_namespaces() const {
	return ns;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Writes header file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_header_file::write_file(std::string const& directory/*=""*/) const {
	ProLog::pLogger::logf<ProLog::NRM>("Writing header file ");
	ProLog::pLogger::logf<ProLog::LBL>("%s.h", name.c_str());
	ProLog::pLogger::logf<ProLog::NRM>(" to /%s.\n", directory.c_str());
	fflush(stdout);
	std::ofstream header_file;
	std::string file_name = directory + "/" + name + ".h";
	header_file.open(file_name.c_str(), std::ofstream::out);
	std::stringstream ss;
	ss << intro().c_str() << "\n\n";
	ss << include_guard_begin().c_str() << "\n\n";
	for(auto const& it:inc_hdr) {
		ss << include_file(it).c_str() << "\n";
	}
	for(auto const& it:inc_lib) {
		ss << include_lib_file(it).c_str() << "\n";
	}
	ss << "\n";
	for(auto const& it:ns) {
		ss << it << "\n";
	}
	ss << include_guard_end().c_str();
	header_file << ss.rdbuf() << std::endl;
	header_file.close();
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Returns the name of the header file.
/////////////////////////////////////////////////////////////////////////////////////////
std::string c2CPP_header_file::get_name() const {
	return name;
}