#ifndef PARSER_EXPRESSION_POW_HPP
#define PARSER_EXPRESSION_POW_HPP

#include "expression.hpp"

namespace mtl {

	class PowExpr : public BinaryOpExpr {
	public:
		PowExpr(Expression* lhs, Expression* rhs) : BinaryOpExpr("^^", lhs, rhs) { }

		virtual std::string cpp_codegen() const
		{
			std::ostringstream s;
			s << "std::pow(" << this->lhs_->cpp_codegen() << ", " << this->rhs_->cpp_codegen() << ")";
			return s.str();
		}
		
		virtual Type type() const
       		{
			choose_number_type(this->line_number, "^^", this->lhs_->type(), this->rhs_->type());
			return this->lhs_->type();
	       	}
		
	};

}

#endif /*PARSER_EXPRESSION_POW_HPP*/
