#include "json/token.h"

namespace json {
	Token::Token(TokenType t, std::string_view l) : type(t), lexeme(l) {}
}