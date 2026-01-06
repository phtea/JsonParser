#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <variant>

namespace json {

	struct Null {};
	struct Value;

	using Array = std::vector<Value>;
	using Object = std::unordered_map<std::string, Value>;

	struct Value {
		using Variant = std::variant<
			Null,
			bool,
			double,
			std::string,
			Array,
			Object>;

		Variant data;
	};

}