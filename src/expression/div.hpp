#ifndef PARSER_EXPRESSION_DIV_HPP
#define PARSER_EXPRESSION_DIV_HPP

#include "expression.hpp"

namespace mtl {

	class DivExpr : public BinaryOpExpr {
	public:
		DivExpr(Expression* lhs, Expression* rhs) : BinaryOpExpr("/", lhs, rhs) { }

		virtual Type* type() const
       		{
			return nullptr;
	       	}
	};

}

#endif /*PARSER_EXPRESSION_DIV_HPP*/
