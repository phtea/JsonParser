#include "json/parser.h"

namespace json {
	Parser::Parser(std::string_view input) : tokenizer_(input) {}

	Value Parser::parse() {
		//todo
		return Value();
	}
}