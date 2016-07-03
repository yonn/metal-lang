#ifndef METAL_EXPRESSION_HPP
#define METAL_EXPRESSION_HPP

#include "error.hpp"

namespace mtl {

	class Expression {
	public:
		
		Expression(size_t line_number);

		virtual std::string cpp_codegen() const = 0;

		size_t line_number;
	};

}

#endif /*METAL_EXPRESSION_HPP*/
