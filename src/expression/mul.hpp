#ifndef PARSER_EXPRESSION_MUL_HPP
#define PARSER_EXPRESSION_MUL_HPP

#include "expression.hpp"

namespace mtl {

	class MulExpr : public BinaryOpExpr {
	public:
		MulExpr(Expression* lhs, Expression* rhs) : BinaryOpExpr("*", lhs, rhs) { }

		virtual Type* type() const
       		{
			return nullptr;
	       	}
	};

}

#endif /*PARSER_EXPRESSION_MUL_HPP*/
