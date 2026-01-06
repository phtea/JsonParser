#include "json/value.h"
#include <sstream>

namespace json {

	static std::string indent(int level) {
		return std::string(level * 2, ' ');
	}

	std::string pretty_print(const Value& v, int level) {
		return std::visit([&](const auto& value) -> std::string {
			using T = std::decay_t<decltype(value)>;

			int next_level = level + 1;

			if constexpr (std::is_same_v<T, Null>) {
				return "null";
			}
			else if constexpr (std::is_same_v<T, bool>) {
				return value ? "true" : "false";
			}
			else if constexpr (std::is_same_v<T, double>) {
				std::ostringstream oss;
				oss << value;
				return oss.str();
			}
			else if constexpr (std::is_same_v<T, std::string>) {
				return "\"" + value + "\"";
			}
			else if constexpr (std::is_same_v<T, Array>) {
				if (value.empty()) return "[]";

				std::string out = "[\n";
				for (size_t i = 0; i < value.size(); ++i) {
					out += indent(next_level);
					out += pretty_print(value[i], next_level);
					if (i + 1 < value.size()) out += ",";
					out += "\n";
				}
				out += indent(level) + "]";
				return out;
			}
			else if constexpr (std::is_same_v<T, Object>) {
				if (value.empty()) return "{}";

				std::string out = "{\n";
				size_t i = 0;
				for (const auto& [key, val] : value) {
					out += indent(next_level);
					out += "\"" + key + "\": ";
					out += pretty_print(val, next_level);
					if (++i < value.size()) out += ",";
					out += "\n";
				}
				out += indent(level) + "}";
				return out;
			}
		},
			v.data);
	}
}  // namespace json