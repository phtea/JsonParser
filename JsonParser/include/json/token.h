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


	struct Token {
		TokenType type;
		std::string_view lexeme;  // todo: value later
	};
};