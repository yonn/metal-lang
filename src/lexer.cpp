#include "lexer.hpp"

namespace mtl {

	static bool comment = false;

	static bool is_token(const std::string& token);

	static TokenIR classify(const std::string& token, size_t line_num);

	static bool is_whitespace(char c);
	static bool is_letter(char c);
	static bool is_number(char c);
	static bool is_hex_digit(char c);


	static bool is_identifier_token(const std::string& token);
	static bool is_number_token(const std::string& token);
	static bool is_string_token(const std::string& token);
	static bool is_char_token(const std::string& token);
	static bool is_comment_token(const std::string& token);

	const static std::set<std::string> symbols = { "[", "]",
	                                               "{", "}",
	                                               "(", ")",
	                                               "::", ":", ";", ",",
	                                               ".", "..", "...",
						       "=", ":=",
						       "+", "-", "*", "/", "%", "^^",
						       "+=", "-=", "*=", "/=", "%=",
						       "&", "|", "^", "~",
						       "&=", "|=", "^=",
						       "->"
						       "==", "!=", "<=", ">=",
						       ">", "<", "<<", ">>",
						       "++", "--" };

	const static std::set<std::string> keywords = { "int",
		                                        "string",
							"if",
							"else" };
	
	const std::string TokenIR::str() const
	{
		const static std::array<std::string, 8> Type_str = { "Keyword",
		                                                     "Symbol",
							             "String",
							             "Character",
							             "DecNum",
							             "FloatNum",
							             "HexNum",
							             "Identifier" };
		std::ostringstream s;
		s << Type_str[(size_t)this->tid] << "[ " << this->token << " ]";
		return s.str();
	}

	TokenList tokenize(const std::string& line, size_t line_num)
	{
		std::vector<std::string> tokens;
		std::string buf = "";
		for (size_t i = 0; i < line.size(); i++) {
			const char c = line[i];

			if (not is_token(buf + c)) {
				if (comment) {
					comment = false;
					buf = "";
					continue;
				}
				if (buf != "") {
					tokens.push_back(buf);
				}
				buf = "";
				if (not is_whitespace(c)) {
					buf += c;
				}
			} else {
				buf += c;
			}
		}
		if (buf != "") {
			tokens.push_back(buf);
		}
		
		TokenList res;

		for (const auto& t: tokens) {
			res.push_back(classify(t, line_num));
		}

		return res;
	}

	bool is_token(const std::string& token)
	{
		if (is_comment_token(token)) return true; 
		else if (is_string_token(token)) return true;
		else if (is_char_token(token)) return true;
		else if (is_whitespace(token[token.size() - 1])) return false;
		else if (symbols.count(token) == 1) return true;
		else if (keywords.count(token) == 1) return true;
		else if (is_number_token(token)) return true;
		else return is_identifier_token(token);
	}

	TokenIR classify(const std::string& token, size_t line_num)
	{
		TokenIR res;
		res.line_number = line_num;
		res.token = token;

		if (keywords.count(token) == 1) {
			res.tid = TokenIR::Type::Keyword;
		} else if (symbols.count(token) == 1) {
			res.tid = TokenIR::Type::Symbol;
		} else if (token[0] == '"' and token[token.size() - 1] == '"') {
			res.tid = TokenIR::Type::String;
		} else if (token[0] == '\'' and token[token.size() - 1] == '\'') {
			res.tid = TokenIR::Type::Character;
		} else if (is_number_token(token)) {
			auto hex1 = std::count(token.begin(), token.end(), 'x');
			auto hex2 = std::count(token.begin(), token.end(), 'X');
			auto fn = std::count(token.begin(), token.end(), '.');
			if (hex1 != 0 or hex2 != 0) {
				if (fn != 0) {
					error(line_num, "Hexadecimal number \"%s\" must be a whole number.", token.c_str());
				} else {
					res.tid = TokenIR::Type::HexNum;
				}
			} else if (fn != 0) {
				res.tid = TokenIR::Type::FloatNum;
			} else {
				res.tid = TokenIR::Type::DecimalNum;
			}
		} else if (is_identifier_token(token)){
			res.tid = TokenIR::Type::Identifier;
		} else {
			error(line_num, "Unidentified token \"%s\"", token.c_str());
		}

		return res;
	}

	bool is_whitespace(char c)
	{
		return c == ' '  or
		       c == '\t' or
		       c == '\n';
	}

	bool is_letter(char c)
	{
		return (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z');
	}

	bool is_number(char c)
	{
		return c >= '0' and c <= '9';
	}

	bool is_hex_digit(char c)
	{
		return (c >= 'a' and c <= 'f') or (c >= 'A' and c <= 'f') or is_number(c);
	}

	bool is_identifier_token(const std::string& token)
	{
		if (not is_letter(token[0]) and not (token[0] == '_')) return false;
		for (size_t i = 1; i < token.size(); i++) {
			if (not is_letter(token[i]) and not is_number(token[i]) and not (token[i] == '_')) {
				return false;
			}
		}
		return true;
	}

	bool is_number_token(const std::string& token)
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

	bool is_string_token(const std::string& token)
	{
		if (token[0] == '"') {
			if (token.size() > 2 and token[token.size() - 2] == '"') {
				if (token.size() > 3 and token[token.size() - 3] == '\\') {
					return true;
				}
				return false;
			}
			return true;
		}
		return false;
	}

	bool is_char_token(const std::string& token)
	{
		if (token[0] == '\'') {
			if (token.size() > 2 and token[token.size() - 2] == '\'') {
				return false;
			} else {
				return true;
			}
		}
		return false;
	}

	bool is_comment_token(const std::string& token)
	{
		if (token[0] != '/') return false;
		comment = true;
		if (token[1] == '/') {
			return not (token[token.size() - 1] == '\n');
		} else if (token[1] == '*') {
			return not (token[token.size() - 1] == '/' and token[token.size() - 2] == '*');
		} else {
			comment = false;
			return false;
		}

		return true;
	}

}
