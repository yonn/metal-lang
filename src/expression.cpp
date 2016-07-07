#include "expression.hpp"

namespace mtl {

	Expression::Expression(size_t line_number)
	{
		this->line_number = line_number;
	}

	BinaryOpExpr::BinaryOpExpr(const std::string& op, Expression* l, Expression* r) : Expression(0/*l->line_number*/)
	{
		this->op_ = op;
		this->lhs_ = l;
		this->rhs_ = r;
	}

	std::string BinaryOpExpr::cpp_codegen() const
	{
		std::ostringstream o;
		o << '(' << this->lhs_->cpp_codegen() << ' ' << this->op_ << ' ' << this->rhs_->cpp_codegen() << ')';
		return o.str();
	}

	VariableExpr::VariableExpr(const TokenIR& token) : Expression(token.line_number)
	{
		this->varname_ = token.token;
	}

	std::string VariableExpr::cpp_codegen() const
	{
		return this->varname_;
	}

}
