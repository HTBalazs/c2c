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

#ifndef _CPPCLASS_H_
#define _CPPCLASS_H_

#include "c2CPP_scope.h"
#include "c2CPP_class_member_function.h"
#include <vector>
#include <string>
#include <sstream>

namespace c2c {
	class c2CPP_class : public c2CPP_scope {
		std::string comment="Generated class.";
		std::vector<c2CPP_class_member_type> member_types;
		std::vector<c2CPP_class_member_function> member_functions;
		std::vector<std::string> interface;
	public:
		c2CPP_class(std::string const& n) : c2CPP_scope{"class", n} {}
		std::string open_session() const override;
		std::string close_session() const override;
		void add_member_type(c2CPP_class_member_type const& mtype);
		void add_member_function(c2CPP_class_member_function const& mfunction);
		void add_member_type(std::string const& type, std::string const& name, bool const& c=false, std::string const& f="", std::string const& init="", accessibility const& a=PRIVATE);
		void add_member_function(std::string const& type, std::string const& name, bool const& c, std::string const& f="", std::vector<c2CPP_declaration> const& args=std::vector<c2CPP_declaration>{}, accessibility const& a=PRIVATE, std::string const& con="", bool const& fc=false, bool const& ovr=false);
		void add_comment(std::string const& c);
		void add_interface(std::string const& parent);
		c2CPP_class_member_function& get_member_function(std::string const& n);
		std::vector<c2CPP_class_member_function> get_member_functions() const;
		friend std::stringstream& operator<<(std::stringstream& ss, c2CPP_class const& cl);
	};

	inline std::stringstream& operator<<(std::stringstream& ss, c2CPP_class const& cl) {
		ss << std::string(cl.level, '\t').c_str() << "// " << cl.comment << "\n";
		ss << cl.open_session().c_str();
		auto write_members = [&](accessibility const& acc_enum) {
			int i = 0;
			std::string acc_str;
			switch(acc_enum) {
				default:
				case PUBLIC: acc_str = "public"; break;
				case PROTECTED: acc_str = "protected"; break;
				case PRIVATE: acc_str = "private"; break;
			}
			for(auto const& it:cl.member_types) {
				if(it.get_accessibility()!=acc_enum) continue;
				if(i++ == 0) ss << std::string(cl.level, '\t').c_str() << acc_str <<":\n";
				ss << std::string(cl.level+1, '\t').c_str();
				ss << it << ";\n";
			}
			for(auto const& it:cl.member_functions) {
				if(it.get_accessibility()!=acc_enum) continue;
				if(i++ == 0) ss << std::string(cl.level, '\t').c_str() << acc_str <<":\n";
				if(it.get_accessibility()==acc_enum){
					ss << std::string(cl.level+1, '\t').c_str();
					ss << it << "\n";
				}
			}
		};
		write_members(PRIVATE);
		write_members(PROTECTED);
		write_members(PUBLIC);
		ss << cl.close_session().c_str();
		return ss;
	}
}

#endif //_CPPCLASS_H_
