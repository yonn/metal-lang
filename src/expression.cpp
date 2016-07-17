#include "expression.hpp"

namespace mtl {

	Expression::Expression(size_t line_number)
	{
		this->line_number = line_number;
	}

	BinaryOpExpr::BinaryOpExpr(const std::string& op, Expression* l, Expression* r) : Expression(l->line_number)
	{
		this->op_ = op;
		this->lhs_ = l;
		this->rhs_ = r;
	}

	std::string BinaryOpExpr::type() const
	{
		return "Unimplemented";
	}

	std::string BinaryOpExpr::cpp_codegen() const
	{
		std::ostringstream o;
		o << '(' << this->lhs_->cpp_codegen() << ' ' << this->op_ << ' ' << this->rhs_->cpp_codegen() << ')';
		return o.str();
	}


	UnaryOpExpr::UnaryOpExpr(const std::string& op, Expression* e, bool post) : Expression(e->line_number)
	{
		this->op_ = op;
		this->e_ = e;
		this->post_ = post;
	}

	std::string UnaryOpExpr::type() const
	{
		return "Unimplemented";
	}
	
	std::string UnaryOpExpr::cpp_codegen() const
	{
		if (this->post_) {
			return this->e_->cpp_codegen() + this->op_;
		} else {
			return this->op_ + this->e_->cpp_codegen();
		}
	}

	VariableExpr::VariableExpr(const TokenIR& token) : Expression(token.line_number)
	{
		this->varname_ = token.token;
	}

	std::string VariableExpr::type() const
	{
		return "Unimplemented";
	}

	std::string VariableExpr::cpp_codegen() const
	{
		return this->varname_;
	}

	LiteralExpr::LiteralExpr(const TokenIR& token) : Expression(token.line_number)
	{
		this->type_ = token.tid;
		this->literal_ = token.token;
	}

	std::string LiteralExpr::type() const
	{
		switch (this->type_) {
		case TokenIR::Type::String:
			return "std::string";
		case TokenIR::Type::Character:
			return "char";
		case TokenIR::Type::DecimalNum:
		case TokenIR::Type::HexNum:
			return "long";
		case TokenIR::Type::FloatNum:
			return "double";
		default:
			error(this->line_number, "Could not identify literal type.");
			return "";
		}
	}

	std::string LiteralExpr::cpp_codegen() const
	{
		return this->literal_;
	}
	
}
