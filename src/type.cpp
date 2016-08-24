#include "type.hpp"

namespace mtl {

	Int::Int(size_t size, bool sign)
	{
		this->size = size;
		this->sign = sign;
	}

	std::string Int::type() const
	{
		size_t size = this->size;
		switch (this->size) {
		case 0:
			size = sizeof(int);
		default:
			return ((this->sign)? "i" : "u") + std::to_string(size);
		}
	}

	std::string Int::cpp_codegen() const
	{
		switch (this->size) {
		case 0:
			return "int";
		default:
			return ((this->sign)? "int" : "uint") + std::to_string(size) + "_t";
		}
	}

	std::string String::type() const
	{
		return "string";
	}

	std::string String::cpp_codegen() const
	{
		return "std::string";
	}
	
}
