#ifndef METAL_ERROR_HPP
#define METAL_ERROR_HPP

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <map>

namespace mtl {
	
	extern std::string error_filename;
	extern std::map<size_t, std::string> lines;
	
	void error(std::string fmt, ...);
	void error(size_t line_number, std::string fmt, ...);
	
}

#endif /*METAL_ERROR_HPP*/
