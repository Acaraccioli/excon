cmake_minimum_required (VERSION 3.0)
project (semantico)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_custom_command(
    OUTPUT Tokens.h lexer.cpp
    COMMAND fa2lexer --hdr Tokens.h --src lexer.cpp --tpl ${PROJECT_SOURCE_DIR}/fa/expr_lexer.fa2l
)

add_executable(${PROJECT_NAME}
                    main.cpp
                    Expressions.cpp
                    ExprLexer.cpp
                    Parser.cpp)

target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ )