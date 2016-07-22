#include "expression.hpp"

namespace mtl {

	BinaryOpExpr* make_binary_expr(const std::string& op, Expression* lhs, Expression* rhs)
	{
		if (op == "+") {
			return new AddExpr(lhs, rhs);
		}
		error(lhs->line_number, "Unsupported binary operator `%s'.", op.c_str());
		return nullptr;
	}

	UnaryOpExpr* make_unary_expr(const std::string& op, Expression* e, bool post)
	{
		error(e->line_number, "Unsupported unary operator `%s'.", op.c_str());
		return nullptr;
	}

}
