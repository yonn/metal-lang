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

		std::cout << "{" << std::endl;
		for (const auto& t: tokens) {
			std::cout << "\t" << t.str() << std::endl;
		}
		std::cout << "}" << std::endl;

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

	const static std::array<std::string, 2> binary_operators = { "+",
	                                                             "*" };

	/*private*/ Expression* Parser::parse_expression_impl(const expr_iter& begin, const expr_iter& end)
	{
		for (const std::string& op: binary_operators) {
			expr_iter p = std::find_if(begin, end, [=](const TokenIR& t) { return t.token == op; });
			if (p != end) {
				return new BinaryOpExpr(op,
				                        parse_expression_impl(begin, p),
				                        parse_expression_impl(p + 1, end));
			}
		}
		
		return parse_atom_impl(begin, end);
	}

	Expression* Parser::parse_atom_impl(const expr_iter& begin, const expr_iter& end)
	{
		return nullptr;
	}
}
