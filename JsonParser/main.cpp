#include "json/parser.h"
#include <iostream>
#include <assert.h>
#include "json/value.h"

void test_1() {
	json::Tokenizer t("{[ ]  }");

	auto a = t.peek();
	auto b = t.peek();
	auto c = t.next();
	auto d = t.next();

	assert(to_string(a.type) == "LBrace");
	assert(to_string(b.type) == "LBrace");
	assert(to_string(c.type) == "LBrace");
	assert(to_string(d.type) == "LBracket");
}

void test_2() {
	json::Parser p("[[[],[],[]]]");
	json::Value v = p.parse();

	assert(!v.data.valueless_by_exception());

	using json::Array;

	const Array& outer = std::get<Array>(v.data);
	assert(outer.size() == 1);

	const Array& inner = std::get<Array>(outer[0].data);
	assert(inner.size() == 3);
}

void test_3() {
	json::Parser p("[null,true,false]");
	auto v = p.parse();

	using json::Array;
	const Array& a = std::get<Array>(v.data);
	assert(std::holds_alternative<json::Null>(a[0].data));
	assert(std::get<bool>(a[1].data) == true);
	assert(std::get<bool>(a[2].data) == false);
}

void test_4() {
	json::Parser p(R"(["hello","world"])");
	auto v = p.parse();

	using json::Array;
	const Array& a = std::get<Array>(v.data);
	assert(std::get<std::string>(a[0].data) == "hello");
	assert(std::get<std::string>(a[1].data) == "world");
}

void test_5() {
	json::Parser p("[1, 3.14, -2]");
	auto v = p.parse();

	using json::Array;
	const Array& a = std::get<Array>(v.data);

	assert(std::get<double>(a[0].data) == 1);
	assert(std::get<double>(a[1].data) == 3.14);
	assert(std::get<double>(a[2].data) == -2);
}

int main() {
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();
}