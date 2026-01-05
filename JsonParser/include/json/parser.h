#pragma once

#include <string_view>
#include "json/value.h"
#include "json/tokenizer.h"

namespace json {
	class Parser {
	public:
		explicit Parser(std::string_view input);

		Value parse();

		Value parse_value();
		Value parse_object();
		Value parse_array();

	private:
		Tokenizer tokenizer_;

		void consume(TokenType expected);
		bool match(TokenType type);
	};
}