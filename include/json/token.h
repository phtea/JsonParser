#pragma once
#include <string_view>

namespace json {
	enum class TokenType {
		LBrace,
		RBrace,
		LBracket,
		RBracket,
		Colon,
		Comma,
		String,
		Number,
		True,
		False,
		Null,
		End
	};

	constexpr std::string_view to_string(TokenType type) {
		switch (type) {
		case TokenType::LBrace:
			return "LBrace";
		case TokenType::RBrace:
			return "RBrace";
		case TokenType::LBracket:
			return "LBracket";
		case TokenType::RBracket:
			return "RBracket";
		case TokenType::Colon:
			return "Colon";
		case TokenType::Comma:
			return "Comma";
		case TokenType::String:
			return "String";
		case TokenType::Number:
			return "Number";
		case TokenType::True:
			return "True";
		case TokenType::False:
			return "False";
		case TokenType::Null:
			return "Null";
		case TokenType::End:
			return "End";
		}
		return "Unknown";
	}


	struct Token {
		Token(TokenType type, std::string_view lexeme);

		TokenType type;
		std::string_view lexeme;  // todo: value later
	};
};