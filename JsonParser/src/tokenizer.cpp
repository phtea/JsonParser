#include "json/tokenizer.h"

namespace json {
	Tokenizer::Tokenizer(std::string_view input) : pos_(0), input_(input) {}

	Token Tokenizer::next() {
		return Token();
	}

	const Token& Tokenizer::peek() {
		// TODO: insert return statement here
		//return Token;
		throw "unimplemented";
	}

	void Tokenizer::skip_whitespace() {
	}
}