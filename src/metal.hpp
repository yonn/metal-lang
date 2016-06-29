#ifndef METAL_METAL_HPP
#define METAL_METAL_HPP

#include <fstream>
#include <map>

#include "lexer.hpp"

namespace mtl {

	extern std::map<size_t, std::string> lines;
	
	TokenList tokenize_file(const std::string& filename);
	
}

#endif /*METAL_METAL_HPP*/
