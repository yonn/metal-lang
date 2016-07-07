#include "expression.hpp"

namespace mtl {

	Expression::Expression(size_t line_number)
	{
		this->line_number = line_number;
	}

	BinaryOpExpr::BinaryOpExpr(std::string op, Expression* l, Expression* r) : Expression(0/*l->line_number*/)
	{
		this->op_ = op;
		this->lhs_ = l;
		this->rhs_ = r;
	}

	std::string BinaryOpExpr::cpp_codegen() const
	{
		std::ostringstream o;
		o << "(RHS " << this->op_ << " LHS)";
		return o.str();
	}

}
