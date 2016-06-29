#ifndef METAL_METAL_HPP
#define METAL_METAL_HPP

#include <fstream>

#include "lexer.hpp"
#include "error.hpp"

namespace mtl {

	TokenList tokenize_file(const std::string& filename);
	
}

#endif /*METAL_METAL_HPP*/
