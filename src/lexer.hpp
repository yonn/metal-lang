#ifndef METAL_LEXER_HPP
#define METAL_LEXER_HPP

#include <list>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

#include "error.hpp"

namespace mtl {

	class TokenIR {
	public:
		
		enum class Type {
			Keyword,
			Symbol,
			String,
			Character,
			DecimalNum,
			FloatNum,
			HexNum,
			Identifier
		} tid;

		std::string token;

		size_t line_number;

		const std::string str() const;
	};
	
	using TokenList = std::list<TokenIR>;
	
	TokenList tokenize(const std::string& line, size_t line_num);

}

#endif /*METAL_LEXER_HPP*/
