#include "json/tokenizer.h"
#include <cctype>
#include <stdexcept>

namespace json {
	Tokenizer::Tokenizer(std::string_view input) : pos_(0), input_(input) {}

	bool Tokenizer::pos_at_end() const {
		return pos_ == input_.size();
	}

	Token Tokenizer::next() {
		skip_whitespace();
		auto start = pos_;
		if (pos_at_end()) { return Token(TokenType::End, ""); }
		switch (input_[pos_]) {
		case '{':
			return Token(TokenType::LBrace, input_.substr(start, ++pos_ - start));
		case '}':
			return Token(TokenType::RBrace, input_.substr(start, ++pos_ - start));
		case '[':
			return Token(TokenType::LBracket, input_.substr(start, ++pos_ - start));
		case ']':
			return Token(TokenType::RBracket, input_.substr(start, ++pos_ - start));
		case ':':
			return Token(TokenType::Colon, input_.substr(start, ++pos_ - start));
		case ',':
			return Token(TokenType::Comma, input_.substr(start, ++pos_ - start));
		}
		//while (!pos_at_end() /*&& !std::isspace(input_[pos_]) maybe this?? */) { pos_++; }
		// if this TokenType this else that
		// the parsing logic here i guess
		throw std::runtime_error("Unexpected character");
		//return Token(TokenType::Number, input_.substr(start, pos_-start+1)); // for now let's say it's a number
	}

	const Token& Tokenizer::peek() {
		// TODO: insert return statement here
		//return Token;
		throw "unimplemented";
	}

	void Tokenizer::skip_whitespace() {
		while (!pos_at_end() && std::isspace(input_[pos_])) { pos_++; }
	}
}