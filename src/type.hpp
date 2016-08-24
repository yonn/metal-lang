#ifndef METAL_TYPE_HPP
#define METAL_TYPE_HPP

#include <string>
#include <map>

#include "error.hpp"

namespace mtl {

	class Type {
	public:

		virtual std::string type() const = 0;
		virtual std::string cpp_codegen() const = 0;
		
	};

	class Int: public Type {
	public:

		Int(size_t size, bool sign);
		
		virtual std::string type() const;
		virtual std::string cpp_codegen() const;

		size_t size;
		bool sign;
		
	};

	
	class String: public Type {
		
		virtual std::string type() const;
		virtual std::string cpp_codegen() const;
		
	};
	
}

#endif /*METAL_TYPE_HPP*/
