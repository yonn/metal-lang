#include "parser.hpp"

namespace mtl {

	Parser::Parser(const TokenList& tokens)
	{
		this->running_ = true;
		this->tokens_ = tokens;
	}

	bool Parser::running()
	{
		return this->running_;
	}

	Expression* Parser::parse_expression()
	{
		std::vector<TokenIR> tokens;
		auto tok = this->next();
		while (this->running_ and tok.token != "{" and tok.token != ";") {
			tokens.push_back(tok);
			tok = this->next();
		}
		this->return_token(tok);

		return parse_expression_impl(tokens.begin(), tokens.end());
	}

	/*private*/ TokenIR Parser::next()
	{
		if (this->tokens_.size() > 0) {
			auto tmp = this->tokens_.front();
			this->tokens_.pop_front();
			return tmp;
		} else {
			this->running_ = false;
			return TokenIR();
		}
	}

	/*private*/ TokenIR Parser::peek()
	{
		return this->tokens_.front();
	}

	/*private*/ void Parser::return_token(const TokenIR& t)
	{
		this->tokens_.push_front(t);
		this->running_ = true;
	}

	std::set<std::string> opening_symbols = { "{", "(", "[" };

	std::set<std::string> closing_symbols = { "}", ")", "]" };

	typedef bool (*BinOpMatch)(const std::string&);

	std::array<BinOpMatch,  2> binary_operator_matches = {
	                                                       [](const auto& s) {
							               return s == "+" or s == "-";
							       },
							       [](const auto &s) {
							               return s == "*" or s == "/";
							       }
		                                             };

	/*private*/ Expression* Parser::parse_expression_impl(const expr_iter& begin, const expr_iter& end)
	{
		size_t level = 0;
		for (auto match: binary_operator_matches) {
			for (auto p = end - 1; p != begin - 1; --p) {
				if (p->tid == TokenIR::Type::Symbol) {
					if (closing_symbols.count(p->token) == 1) {
						level++;
					} else if (opening_symbols.count(p->token) == 1) {
						level--;
					} else if (level == 0) {
						if (match(p->token)) {
							return new BinaryOpExpr(p->token,
							                        parse_expression_impl(begin, p),
										parse_expression_impl(p + 1, end));
						}
					}
				}
			}
		}
		return parse_atom_impl(begin, end);
	}

	Expression* Parser::parse_atom_impl(const expr_iter& begin, const expr_iter& end)
	{
		if (begin + 1 == end) {
			if (begin->tid == TokenIR::Type::Identifier) {
				return new VariableExpr(*begin);
			}
		} else {
			if (begin->tid == TokenIR::Type::Identifier) {
				//function call
			} else {
				if (begin->token == "(") {
					return parse_expression_impl(begin + 1, end - 1);
				}
			}
		}
		return nullptr;
	}
}
