cmake_minimum_required(VERSION 3.20)

project(JsonParser
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(json_parser
    src/tokenizer.cpp
    src/token.cpp
    src/parser.cpp
    src/pretty_print.cpp
)

target_include_directories(json_parser
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(json_parser_app
    main.cpp
)

target_link_libraries(json_parser_app
    PRIVATE json_parser
)
