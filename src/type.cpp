#include "type.hpp"

namespace mtl {

	Type::Type(const std::string& s)
	{
		this->type_ = s;
	}

	std::string Type::str() const
	{
		return this->type_;
	}
	
	std::map<Type, int> numbers = { { Type("i8"), 0 },
	                                { Type("char"), 0 },
	                                { Type("u8"), 1 },
					{ Type("i16"), 2 },
					{ Type("short"), 2 },
					{ Type("u16"), 3 },
					{ Type("i32"), 4 },
					{ Type("int"), 4 },
					{ Type("f32"), 5 },
					{ Type("float"), 5 },
					{ Type("u32"), 6 },
					{ Type("i64"), 7 },
					{ Type("long"), 7 },
					{ Type("u64"), 8 },
	                                { Type("double"), 9},
	                                { Type("f64"), 9} };

	bool operator==(const Type& l, const Type& r)
	{
		return r.type_ == l.type_;
	}

	bool operator<(const Type& l, const Type& r)
	{
		return r.type_ < l.type_;
	}


	Type choose_number_type(size_t line_number, std::string op, const Type& l, const Type& r)
	{
		if (numbers.count(l) == 0 or numbers.count(r) == 0) {
			error(line_number, "Unsuported types for operator `%s'.\n"
				           "This operation supports only primative interger types, not:\n"
			                   "\"%s\", and \"%s\"", op.c_str(), l.str().c_str(), r.str().c_str());
			return Type("");
		}
		
		if (numbers[r] < numbers[l]) {
			return l;
		} else {
			return r;
		}
	}

}
