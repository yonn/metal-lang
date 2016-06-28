#ifndef METAL_LEXER_HPP
#define METAL_LEXER_HPP

#include <vector>
#include <string>
#include <set>
#include <algorithm>

namespace mtl {

	class TokenIR {
	public:
		
		enum class Identifier{
			Keyword,
			Symbol,
			String,
			Number,
			Identifier
		} id;

		std::string token;

		size_t line_number;

		const std::string str() const;
	};
	
	using TokenList = std::vector<TokenIR>;
	
	std::vector<std::string> tokenize(const std::string& line, size_t line_num);

}

#endif /*METAL_LEXER_HPP*/
