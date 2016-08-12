#ifndef METAL_EXPRESSION_HPP
#define METAL_EXPRESSION_HPP

#include <string>
#include <sstream>

#include "lexer.hpp"
#include "error.hpp"

#include "expression/expression.hpp"

#include "expression/add.hpp"
#include "expression/sub.hpp"
#include "expression/div.hpp"
#include "expression/mul.hpp"

namespace mtl {

	BinaryOpExpr* make_binary_expr(const std::string& op, Expression* lhs, Expression* rhs);
	UnaryOpExpr* make_unary_expr(const std::string& op, Expression* e, bool post = false);

}

#endif /*METAL_EXPRESSION_HPP*/
