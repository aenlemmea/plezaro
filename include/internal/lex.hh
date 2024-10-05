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
    RPAREN = ')'
};

struct TOKEN {
  std::size_t line = 1L;
  std::string token_value;
  TOKEN_TYPE type;
  TOKEN(TOKEN_TYPE tp, std::size_t ln, std::string tv)
  : line(ln), token_value(tv), type(tp) {}; 
  
};

class Lexer {
public:
  Lexer(const std::stringstream& src) : source_stream(src) {}
  [[nodiscard("Should use the token")]] static TOKEN lex(void);
private:
  const std::stringstream& source_stream;
};

#endif



