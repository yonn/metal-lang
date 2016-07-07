#ifndef METAL_EXPRESSION_HPP
#define METAL_EXPRESSION_HPP

#include <string>
#include <sstream>

#include "lexer.hpp"
#include "error.hpp"

namespace mtl {

	class Expression {
	public:
		
		Expression(size_t line_number);

		virtual std::string cpp_codegen() const = 0;

		size_t line_number;
	};

	class BinaryOpExpr : public Expression {
	public:

		BinaryOpExpr(const std::string& op, Expression* l, Expression* r);
		
		virtual std::string cpp_codegen() const;

	protected:
		
		std::string op_;

		Expression* rhs_;
		Expression* lhs_;
	
	};

	class VariableExpr : public Expression {
	public:
		
		VariableExpr(const TokenIR& token);

		virtual std::string cpp_codegen() const;

	protected:
		
		std::string varname_;
	};

}

#endif /*METAL_EXPRESSION_HPP*/