#include "json/parser.h"

namespace json {

Parser::Parser(std::string_view input) : input_(input), pos_(0) {}

Value Parser::parse() {
	//todo
	return Value();
}

}