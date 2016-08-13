#ifndef METAL_TYPE_HPP
#define METAL_TYPE_HPP

#include <string>
#include <map>

#include "error.hpp"

namespace mtl {

	class Type {
	public:
		
		Type(const std::string& s);

		std::string str() const;
			
		std::string type_;
		
	};

	bool operator==(const Type& l, const Type& r);
	bool operator<(const Type& l, const Type& r);
	
	extern std::map<Type, int> numbers;

	Type choose_number_type(size_t line_number, std::string op, const Type& l, const Type& r);
	
}

#endif /*METAL_TYPE_HPP*/
