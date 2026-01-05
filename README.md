# JSON Parser (C++)

A learning-focused JSON parser implemented in modern C++, designed to explore tokenizer-parser architecture, recursive descent parsing, and `std::variant`-based AST design.

The parser converts JSON text into a strongly typed in-memory representation that can be accessed through a simple, high-level API.

---

## Build

This project is built using a Visual Studio solution.

### Requirements
- Windows
- Visual Studio 2022 (or newer)
- C++17 or newer

### Steps
1. Open `JsonParser.slnx` in Visual Studio
2. Select the desired build configuration (`Debug` or `Release`)
3. Build the solution (`Ctrl + Shift + B`)
4. Run the project (`F5` or `Ctrl + F5`)

---

## Features

- Recursive-descent JSON parser
- Custom tokenizer with one-token lookahead
- Ownership-safe value model using `std::variant`
- Fully materialized AST (objects, arrays, literals)
- Clean separation of:
  - Lexer (tokenizer)
  - Parser
  - AST / value model

### Supported JSON constructs

- Objects (`{}`)
- Arrays (`[]`)
- Strings (basic, without escapes)
- Numbers (integers and decimals)
- Literals: `true`, `false`, `null`
- Arbitrary nesting

---

## Example

```cpp
json::Parser parser(R"({"key": [1, 2, 3]})");
json::Value value = parser.parse();

using json::Object;
using json::Array;

const Object& obj = std::get<Object>(value.data);
const Array& arr = std::get<Array>(obj.at("key").data);

std::cout << json::pretty_print(value) << "\n";
````

---

## Not implemented (by design)

The following features are intentionally omitted to keep the project focused on core parsing concepts:

* String escape sequences (`\"`, `\n`, `\t`, `\\`)
* Unicode escapes (`\uXXXX`)
* Exponential numbers (`1e10`)
* Line/column error reporting
* Streaming / incremental parsing
* Performance optimizations (naive implementation for clarity)

---

## Motivation

This project was built as a learning exercise to understand how real parsers are structured in C++, focusing on correctness, clarity, and modern language features rather than completeness or performance.

---

## License

MIT