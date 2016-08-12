#ifndef METAL_EXPRESSION_EXPRESSION_HPP
#define METAL_EXPRESSION_EXPRESSION_HPP

#include <string>
#include <sstream>

#include "../lexer.hpp"
#include "../error.hpp"
#include "../type.hpp"

namespace mtl {

	class Expression {
	public:
		
		Expression(size_t line_number);

		virtual Type type() const = 0;

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

	class UnaryOpExpr : public Expression {
	public:

		UnaryOpExpr(const std::string& op, Expression* e, bool post = false);

		virtual std::string cpp_codegen() const;

	protected:

		bool post_;
		std::string op_;
		Expression* e_;

	};

	class VariableExpr : public Expression {
	public:
		
		VariableExpr(const TokenIR& token);

		virtual Type type() const;

		virtual std::string cpp_codegen() const;

	protected:
		
		std::string varname_;
	};

	class LiteralExpr : public Expression {
	public:
	
		LiteralExpr(const TokenIR& token);
		
		virtual Type type() const;

		virtual std::string cpp_codegen() const;

	protected:

		std::string literal_;
		TokenIR::Type type_;
	};

}

#endif /*METAL_EXPRESSION_EXPRESSION_HPP*/
