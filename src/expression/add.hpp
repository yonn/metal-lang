#ifndef PARSER_EXPRESSION_ADD_HPP
#define PARSER_EXPRESSION_ADD_HPP

#include "expression.hpp"

namespace mtl {

	class AddExpr : public BinaryOpExpr {
	public:
		AddExpr(Expression* lhs, Expression* rhs) : BinaryOpExpr("+", lhs, rhs) { }

		virtual std::string type() const
       		{
				return "Undefined.";
	       	}
	};

}

#endif /*PARSER_EXPRESSION_ADD_HPP*/
