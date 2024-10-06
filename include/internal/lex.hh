#ifndef LEX_HH
#define LEX_HH

// Represents the TOKENS for the language.
// Using a case-sensitive char approach to simplify the thought model.
// Not a good design choice I know, will swap for something better later.
#include <cstddef>
#include <sstream>
#include <string>
enum class TOKEN_TYPE : char {
    IDENT = 'I',
    NUMBER = 'N',
    CONST = 'C',
    VAR = 'V',
    PROCEDURE = 'P',
    CALL = 'c',
    BEGIN = 'B',
    END = 'E',
    IF = 'i',
    THEN = 'T',
    WHILE = 'W',
    DO = 'D',
    ODD = 'O',
    DOT = '.',
    EQUAL = '=',
    COMMA = ',',
    SEMICOLON = ';',
    ASSIGN = ':',
    HASH = '#',
    LESSTHAN = '<',
    GREATERTHAN = '>',
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    LPAREN = '(',
    RPAREN = ')',
    NULL_TERM = '\0',
};

struct TOKEN {
    std::string token_value;
    TOKEN_TYPE type;
  TOKEN(TOKEN_TYPE tp, std::string tv) : token_value(tv), type(tp) { }
    TOKEN(TOKEN_TYPE tp, char tv) : token_value(std::to_string(tv)), type(tp) {}
    TOKEN(TOKEN_TYPE tp, long tv) : token_value(std::to_string(tv)), type(tp) {}
    bool operator==(const TOKEN& other) const {
        return (type == other.type && token_value == other.token_value);
    }
};

class Lexer {
public:
    Lexer(std::stringstream& src) : source_stream(src) {}
    [[nodiscard("Should use the token")]] TOKEN lex(void);

private:
    std::size_t line_num = 1L;
    std::stringstream& source_stream;
    std::string snum_val{};
    std::string iden_val{};
    void comment(void);
    TOKEN identifier(void);
    TOKEN number(void);
};

#endif
