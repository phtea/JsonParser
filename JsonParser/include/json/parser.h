#pragma once

#include <string_view>
#include "json/value.h"
#include "json/tokenizer.h"

namespace json {
	class Parser {
	public:
		explicit Parser(std::string_view input);

		Value parse();

	private:
		Tokenizer tokenizer_;
	};
}