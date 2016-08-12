#ifndef PARSER_EXPRESSION_SUB_HPP
#define PARSER_EXPRESSION_SUB_HPP

#include "expression.hpp"

namespace mtl {

	class SubExpr : public BinaryOpExpr {
	public:
		SubExpr(Expression* lhs, Expression* rhs) : BinaryOpExpr("-", lhs, rhs) { }

		virtual Type type() const
       		{
			return choose_number_type(this->line_number, "-", this->lhs_->type(), this->rhs_->type());
	       	}
	};

}

#endif /*PARSER_EXPRESSION_SUB_HPP*/
