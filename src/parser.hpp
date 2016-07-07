#ifndef METAL_PARSER_HPP
#define METAL_PARSER_HPP

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

#include "expression.hpp"
#include "lexer.hpp"
#include "error.hpp"

namespace mtl {

	class Parser {
	public:

		Parser(const TokenList& tokens);
		
		bool running();

		Expression* parse_expression();
	
	private:

		TokenIR next();
		TokenIR peek();
		void return_token(const TokenIR& t);

		using expr_iter = std::vector<TokenIR>::iterator;

		Expression* parse_expression_impl(const expr_iter& begin, const expr_iter& end);
		Expression* parse_atom_impl(const expr_iter& begin, const expr_iter& end);

		TokenList tokens_;
		bool running_;
	};

}

#endif /*METAL_PARSER_HPP*/
