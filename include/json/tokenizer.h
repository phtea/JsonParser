#pragma once

#include <string_view>
#include <optional>
#include "json/token.h"

namespace json {

	class Tokenizer {
	public:
		explicit Tokenizer(std::string_view input);

		Token next();		  // consume and return
		const Token& peek();  // lookahead

	private:
		std::string_view input_;
		std::size_t pos_;
		std::optional<Token> lookahead_;

		bool pos_at_end() const;
		void skip_whitespace();
		bool match_keyword(std::string_view kw);
		Token read_string();
		Token read_number();
	};

}  // namespace json