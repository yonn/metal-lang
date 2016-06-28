#include "lexer.hpp"

namespace mtl {

	static bool is_token(const std::string& token);

	static bool is_whitespace(char c);
	static bool is_letter(char c);
	static bool is_number(char c);
	static bool is_hex_digit(char c);


	static bool is_identifier(const std::string& token);
	static bool is_number(const std::string& token);

	const static std::set<std::string> symbols = { "[", "]",
	                                                           "{", "}",
								   "(", ")",
								   "::", ":", ";" 
								   "." };

	const static std::set<std::string> keywords = { "int",
		                                                    "string" };

	std::vector<std::string> tokenize(const std::string& line, size_t line_num)
	{
		std::vector<std::string> tokens;
		std::string buf = "";
		for (const auto c: line) {
			if (not is_token(buf + c)) {
				tokens.push_back(buf);
				buf = "";
				if (not is_whitespace(c)) {
					buf += c;
				}
			} else {
				buf += c;
			}
		}
		tokens.push_back(buf);
		return tokens;
	}

	bool is_token(const std::string& token)
	{
		if (is_whitespace(token[token.size() - 1])) return false;
		else if (symbols.count(token) == 1) return true;
		else if (keywords.count(token) == 1) return true;
		else if (is_number(token)) return true;
		else return is_identifier(token);
	}

	bool is_whitespace(char c)
	{
		return c == ' '  or
		       c == '\t' or
		       c == '\n';
	}

	bool is_letter(char c)
	{
		return c >= 'A' and c <= 'z';
	}

	bool is_number(char c)
	{
		return c >= '0' and c <= '9';
	}

	bool is_hex_digit(char c)
	{
		return (c >= 'a' and c <= 'f') or (c >= 'A' and c <= 'f') or is_number(c);
	}

	bool is_identifier(const std::string& token)
	{
		if (not is_letter(token[0]) and not (token[0] == '_')) return false;
		for (size_t i = 1; i < token.size(); i++) {
			if (not is_letter(token[i]) and not is_number(token[i]) and not (token[i] == '_')) {
				return false;
			}
		}
		return true;
	}

	bool is_number(const std::string& token)
	{
		bool period = false;
		bool hex = false;

		if (token.size() >= 2 and token[0] == '0' and (token[1] == 'x' or token[1] == 'X')) hex = true;

		for (size_t i = 0; i < token.size(); i++) {
			auto c = token[i];

			if (hex) {
				if (i < 3) continue;
				if (is_hex_digit(c)) continue;
			}
			
			if (c == '.' and not period) {
				period = true;
				continue;	
			} else if (not is_number(c) and not (c == '_')) {
				return false;
			}
		}
		return true;
	}

}
