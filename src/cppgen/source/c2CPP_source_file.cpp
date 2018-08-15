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

#include "c2CPP_source_file.h"

using namespace c2c;

/////////////////////////////////////////////////////////////////////////////////////////
/// Generates and writes source file.
/////////////////////////////////////////////////////////////////////////////////////////
void c2CPP_source_file::write_file() const {
    std::ofstream source_file;
    std::string file_name = header.get_name() + ".cpp";
    source_file.open(file_name.c_str(), std::ofstream::out);
    std::stringstream ss;
    ss << "#include \"" << header.get_name() << ".h\"\n\n";
    for(auto const& it:header.get_namespaces()) {
        ss << "using namespace " << it.get_name() << ";\n";
    }
    source_file << ss.rdbuf() << std::endl;
    std::vector<c2CPP_namespace> namespaces = header.get_namespaces();
    for(auto const& it_ns:namespaces) {
        for(auto const& it_cl:it_ns.get_classes()) {
            for(auto const& it_mf:it_cl.get_member_functions()) {
                source_file << it_mf.get_definition_code(it_cl.get_name()) << "\n\n";
            }
        }
    }

    for(auto const& it_ns:namespaces) {
        for(auto const& it_cl:it_ns.get_classes()) {
            source_file << "extern \"C\" " << it_cl.get_name() << "* create() {\n\treturn new " <<  it_cl.get_name() << ";\n}\n\n";
        }
    }
    for(auto const& it_ns:namespaces) {
        for(auto const& it_cl:it_ns.get_classes()) {
            source_file << "extern \"C\" void destroy(" << it_cl.get_name() << "* obj) {\n\tdelete obj;\n}\n\n";
        }
    }

    source_file.close();
}