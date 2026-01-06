#include "json/tokenizer.h"
#include <cctype>
#include <stdexcept>

namespace json {
	Tokenizer::Tokenizer(std::string_view input) : pos_(0), input_(input) {}

	bool Tokenizer::pos_at_end() const {
		return pos_ >= input_.size();
	}

	Token Tokenizer::next() {
		// If we already peeked - return cached token
		if (lookahead_) {
			Token tok = *lookahead_;
			lookahead_.reset();
			return tok;
		}

		// Else normal tokenization
		skip_whitespace();

		if (pos_at_end()) {
			return Token{ TokenType::End, "" };
		}

		// Match strings first
		char c = input_[pos_];
		if (c == '"') {
			return read_string();
		}

		if (c == '-' || std::isdigit(static_cast<unsigned char>(c))) {
			return read_number();
		}

		// Match keywords second
		if (match_keyword("null")) {
			return Token{ TokenType::Null, "null" };
		}
		if (match_keyword("true")) {
			return Token{ TokenType::True, "true" };
		}
		if (match_keyword("false")) {
			return Token{ TokenType::False, "false" };
		}

		// Single-char tokens after
		std::size_t start = pos_;
		c = input_[pos_];

		++pos_;

		switch (c) {
			case '{': return Token{ TokenType::LBrace, input_.substr(start, 1) };
			case '}': return Token{ TokenType::RBrace, input_.substr(start, 1) };
			case '[': return Token{ TokenType::LBracket, input_.substr(start, 1) };
			case ']': return Token{ TokenType::RBracket, input_.substr(start, 1) };
			case ':': return Token{ TokenType::Colon, input_.substr(start, 1) };
			case ',': return Token{ TokenType::Comma, input_.substr(start, 1) };
		}

		throw std::runtime_error("Unexpected character");
	}

	// Peek at next element
	const Token& Tokenizer::peek() {
		// Fill lookahead if empty
		if (!lookahead_) {
			lookahead_ = next();
		}
		return *lookahead_;
	}

	void Tokenizer::skip_whitespace() {
		while (!pos_at_end() && std::isspace(input_[pos_])) { ++pos_; }
	}

	bool Tokenizer::match_keyword(std::string_view kw) {
		if (input_.substr(pos_, kw.size()) == kw) {
			pos_ += kw.size();
			return true;
		}
		return false;
	}

	Token Tokenizer::read_string() {
		// current pos_ points at opening quote
		std::size_t start = ++pos_;	 // skip opening "

		while (!pos_at_end() && input_[pos_] != '"') {
			++pos_;
		}

		if (pos_at_end()) {
			throw std::runtime_error("Unterminated string literal");
		}

		std::string_view sv = input_.substr(start, pos_ - start);
		++pos_;	 // consume closing "

		return Token{ TokenType::String, sv };
	}

	Token Tokenizer::read_number() {
		std::size_t start = pos_;

		// optional minus
		if (input_[pos_] == '-') {
			++pos_;
			if (pos_at_end() || !std::isdigit(static_cast<unsigned char>(input_[pos_]))) {
				throw std::runtime_error("Invalid number: '-' not followed by digit");
			}
		}

		// integer part
		while (!pos_at_end() && std::isdigit(static_cast<unsigned char>(input_[pos_]))) {
			++pos_;
		}

		// fractional part
		if (!pos_at_end() && input_[pos_] == '.') {
			++pos_;
			if (pos_at_end() || !std::isdigit(static_cast<unsigned char>(input_[pos_]))) {
				throw std::runtime_error("Invalid number: '.' not followed by digit");
			}
			while (!pos_at_end() && std::isdigit(static_cast<unsigned char>(input_[pos_]))) {
				++pos_;
			}
		}

		std::string_view sv = input_.substr(start, pos_ - start);
		return Token{ TokenType::Number, sv };
	}
}