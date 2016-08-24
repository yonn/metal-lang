#ifndef PARSER_EXPRESSION_SUB_HPP
#define PARSER_EXPRESSION_SUB_HPP

#include "expression.hpp"

namespace mtl {

	class SubExpr : public BinaryOpExpr {
	public:
		SubExpr(Expression* lhs, Expression* rhs) : BinaryOpExpr("-", lhs, rhs) { }

		virtual Type* type() const
       		{
			return nullptr;
	       	}
	};

}

#endif /*PARSER_EXPRESSION_SUB_HPP*/
