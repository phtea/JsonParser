#pragma once

#include <string_view>
#include "json/token.h"

namespace json {

	class Tokenizer {
	public:
		explicit Tokenizer(std::string_view input);

		bool pos_at_end() const;

		Token next();		  // consume and return
		const Token& peek();  // lookahead

	private:
		std::string_view input_;
		std::size_t pos_;

		void skip_whitespace();
		// helpers: advance(), match(), etc.
	};

}  // namespace json