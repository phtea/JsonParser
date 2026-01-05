#pragma once

#include <string>
#include "json/value.h"

namespace json {
	std::string pretty_print(const Value& v, int level = 0);
};