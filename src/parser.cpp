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

	TokenIR Parser::next()
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

	TokenIR Parser::peek()
	{
		return this->tokens_.front();
	}

	void Parser::return_token(const TokenIR& t)
	{
		this->tokens_.push_front(t);
		this->running_ = true;
	}

	const static std::set<std::string> opening_symbols = { "{", "(", "[" };

	const static std::set<std::string> closing_symbols = { "}", ")", "]" };

	const static std::set<std::string> unary_operators = { "+", "-",
	                                                       "++", "--" };

	const static std::array<bool (*)(const std::string&),  2> binary_operator_matches = {
	                                                                                      [](const auto& s) {
                                                                                                return s == "+" or s == "-";
                                                                                              },
                                                                                              [](const auto &s) {
                                                                                                return s == "*" or s == "/";
                                                                                              }
		                                                                            };
	
	static bool is_binary_op(const std::string& op)
	{
		for (auto m: binary_operator_matches) {
			if (m(op)) {
				return true;
			}
		}
		return false;
	}

	Expression* Parser::parse_expression_impl(const expr_iter& begin, const expr_iter& end)
	{
		for (auto match: binary_operator_matches) {
			size_t level = 0;
			for (auto p = end - 1; p != begin - 1; --p) {
				if (p->tid == TokenIR::Type::Symbol) {
					if (closing_symbols.count(p->token) == 1) {
						level++;
					} else if (opening_symbols.count(p->token) == 1) {
						level--;
					} else if (level == 0) {
						if (match(p->token)) {
							if (unary_operators.count(p->token) == 1) {
								if (p == begin) {
									return parse_atom_impl(begin, end);
								} else if (is_binary_op((p - 1)->token)) {
									continue;
								} else {
									goto else__;
								}
							} else {
								else__:
								return make_binary_expr(p->token,
								                        parse_expression_impl(begin, p),
								                        parse_expression_impl(p + 1, end));
							}
						}
					}
				}
			}
			if (level != 0) {
				error(begin->line_number, "Unmatched parenthesis.");
			}
		}
		return parse_atom_impl(begin, end);
	}

	Expression* Parser::parse_atom_impl(const expr_iter& begin, const expr_iter& end)
	{
		if (begin + 1 == end) { //literal
			if (begin->tid == TokenIR::Type::Identifier) { //identifier (variable)
				return new VariableExpr(*begin);
			} else if (begin->tid >= TokenIR::Type::String and begin->tid <= TokenIR::Type::HexNum) {
				return new LiteralExpr(*begin);
			} else {
				goto error__;
			}
		} else {
			if (begin->tid == TokenIR::Type::Identifier and (begin + 1)->token == "(") { // func call
			} else if (begin->tid == TokenIR::Type::Symbol and begin->token != "(") { //prefix symbol
				return make_unary_expr(begin->token, parse_atom_impl(begin + 1, begin + 2));
			} else if ((begin + 1)->tid == TokenIR::Type::Symbol and (begin + 1)->token != "(") { //postfix symbol
				return make_unary_expr((begin + 1)->token, parse_atom_impl(begin, begin + 1), true);
			} else if (begin->token == "(") { //parenthesis
					return parse_expression_impl(begin + 1, end - 1);
			} else {
				goto error__;
			}
		}
	error__:
		error(begin->line_number, "Unknown tokens in expression.");
		return nullptr;
	}
}
