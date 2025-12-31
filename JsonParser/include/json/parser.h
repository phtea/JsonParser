#pragma once

#include <string_view>
#include "json/value.h"

namespace json {

class Parser {
public:
	explicit Parser(std::string_view input);

	Value parse();

private:
	// cursor state
	std::string_view input_;
	std::size_t pos_;

};

}