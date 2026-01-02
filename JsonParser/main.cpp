#include "json/parser.h"
#include <iostream>

int main() {
	std::string_view input("{ [            ] }");
	std::cout << "Input: " << input << std::endl;

	json::Tokenizer t(input);
	for (int i = 0;;i++) {
		auto tok = t.next();
		if (tok.type == json::TokenType::End) break;
		std::cout << i << ". type: " << json::to_string(tok.type)
			<< ", lexeme: " << tok.lexeme << std::endl;
	}
}