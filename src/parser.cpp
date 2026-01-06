#include "json/parser.h"
#include <stdexcept>
#include <string>

namespace json {
	Parser::Parser(std::string_view input) : tokenizer_(input) {}

	Value Parser::parse() {
		return parse_value();
	}

	Value Parser::parse_value() {
		Token tok = tokenizer_.peek();

		switch (tok.type) {
			case TokenType::LBrace: tokenizer_.next(); return parse_object();
			case TokenType::LBracket: tokenizer_.next(); return parse_array();
			case TokenType::String: tokenizer_.next(); return Value{ std::string(tok.lexeme) };
			case TokenType::Number:
				tokenizer_.next();
				return Value{ std::stod(std::string(tok.lexeme)) };
			case TokenType::True: tokenizer_.next(); return Value{ true };
			case TokenType::False: tokenizer_.next(); return Value{ false };
			case TokenType::Null: tokenizer_.next(); return Value{ Null{} };
			default: throw std::runtime_error("Non-existent token type");
		}
	}

	Value Parser::parse_object() {
		Object obj;

		if (tokenizer_.peek().type != TokenType::RBrace) {
			do {
				Token key = tokenizer_.next(); //key
				if (key.type != TokenType::String) {
					throw std::runtime_error("Expected string key");
				}

				consume(TokenType::Colon); //colon
				Value val = parse_value(); //value

				obj.emplace(std::string(key.lexeme), val); 

			} while (match(TokenType::Comma));
		}

		consume(TokenType::RBrace);
		return Value{ obj };
	}

	Value Parser::parse_array() {
		Array arr;

		if (tokenizer_.peek().type != TokenType::RBracket) {
			do {
				arr.push_back(parse_value());
			} while (match(TokenType::Comma));
		}

		consume(TokenType::RBracket);
		return Value{arr};
	}

	void Parser::consume(TokenType expected) {
		Token tok = tokenizer_.next();
		if (tok.type != expected) {
			throw std::runtime_error("Unexpected token");
		}
	}

	bool Parser::match(TokenType type) {
		if (tokenizer_.peek().type == type) {
			tokenizer_.next();
			return true;
		}
		return false;
	}
}