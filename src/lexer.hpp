#ifndef METAL_LEXER_HPP
#define METAL_LEXER_HPP

#include <vector>
#include <string>

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
	
	TokenList tokenize(std::string line);
}

#endif /*METAL_LEXER_HPP*/
