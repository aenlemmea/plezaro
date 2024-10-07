#include "internal/lex.hh"
#include "log.hh"

#include <cctype>
#include <iostream>
#include <stdexcept>

void Lexer::comment() {
    char ch;
    while ((source_stream.get(ch)) && ch != '}') {
        if (ch == source_stream.eof()) {
            std::cerr << "Unterminated comment. @ " << line_num << std::endl;
            exit(-1);
        }

        if (ch == '\n') {
            line_num++;
        }
    };
}

TOKEN Lexer::number() {
    char ch;

    while ((source_stream.get(ch)) && (isdigit(ch) || ch == '_')) {
        snum_val.push_back(ch);
    }

    long num_val{};
    try {
        num_val = std::stol(snum_val);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid Number: " << e.what() << std::endl;
        exit(-1);
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        exit(-1);
    }
    return TOKEN(TOKEN_TYPE::NUMBER, num_val);
}

TOKEN Lexer::identifier() {
    char ch;
    while ((source_stream.get(ch)) && (isalnum(ch) || ch == '_')) {
        iden_val.push_back(ch);
    }

    // See that one CPP conf talk on template specializations to avoid branching for the fix later.
    // I know I know. Will do some template shenanigans later to avoid this.
    if (iden_val == "CONST") {
        return TOKEN(TOKEN_TYPE::CONST, iden_val);
    }
    else if (iden_val == "VAR") {
        return TOKEN(TOKEN_TYPE::VAR, iden_val);
    }
    else if (iden_val == "PROCEDURE") {
        return TOKEN(TOKEN_TYPE::PROCEDURE, iden_val);
    }
    else if (iden_val == "CALL") {
        return TOKEN(TOKEN_TYPE::CALL, iden_val);
    }
    else if (iden_val == "BEGIN") {
        return TOKEN(TOKEN_TYPE::BEGIN, iden_val);
    }
    else if (iden_val == "END") {
        return TOKEN(TOKEN_TYPE::END, iden_val);
    }
    else if (iden_val == "IF") {
        return TOKEN(TOKEN_TYPE::IF, iden_val);
    }
    else if (iden_val == "THEN") {
        return TOKEN(TOKEN_TYPE::THEN, iden_val);
    }
    else if (iden_val == "WHILE") {
        return TOKEN(TOKEN_TYPE::WHILE, iden_val);
    }
    else if (iden_val == "DO") {
        return TOKEN(TOKEN_TYPE::DO, iden_val);
    }
    else if (iden_val == "ODD") {
        return TOKEN(TOKEN_TYPE::ODD, iden_val);
    }

    return TOKEN(TOKEN_TYPE::IDENT, iden_val);
}

TOKEN Lexer::lex(void) {
    char ch = source_stream.peek();
    // FIXME: Write a better whitespace skip function.
    while (ch == ' ' || ch == '\t' || ch == '\n') {
        ch = source_stream.get();
        if (ch == '\n') {
            line_num++;
        }
        else {
            if (isalpha(ch) || ch == '_') {
                iden_val.push_back(ch);
            }
            if (isdigit(ch)) {
                snum_val.push_back(ch);
            }
            break;
        }
    }
  
    if (source_stream.eof()) {
        return TOKEN(TOKEN_TYPE::NULL_TERM, '\0');
    }

    source_stream.get(ch);

    // Repeated code. Bad choices. YEP
    if (isalpha(ch) || ch == '_') {
        iden_val.push_back(ch);
        return identifier();
    }
    if (isdigit(ch)) {
      snum_val.push_back(ch);
      return number();
    }

    switch (ch) {
        case '{':
            comment();
            break;
        case '.':
            return TOKEN(TOKEN_TYPE::DOT, ch);
        case '=':
            return TOKEN(TOKEN_TYPE::EQUAL, ch);
        case ',':
            return TOKEN(TOKEN_TYPE::COMMA, ch);
        case ';':
            return TOKEN(TOKEN_TYPE::SEMICOLON, ch);
        case '#':
            return TOKEN(TOKEN_TYPE::HASH, ch);
        case '<':
            return TOKEN(TOKEN_TYPE::LESSTHAN, ch);
        case '>':
            return TOKEN(TOKEN_TYPE::GREATERTHAN, ch);
        case '+':
            return TOKEN(TOKEN_TYPE::PLUS, ch);
        case '-':
            return TOKEN(TOKEN_TYPE::MINUS, ch);
        case '*':
            return TOKEN(TOKEN_TYPE::MULTIPLY, ch);
        case '/':
            return TOKEN(TOKEN_TYPE::DIVIDE, ch);
        case '(':
            return TOKEN(TOKEN_TYPE::LPAREN, ch);
        case ')':
            return TOKEN(TOKEN_TYPE::RPAREN, ch);
        case ':':
            ch = source_stream.get();
            if (ch != '=') {
                std::cerr << "Unknown TOKEN_TYPE @ " << line_num << " : " << ch << std::endl;
                exit(-1);
            }
            ch = ':';
            return TOKEN(TOKEN_TYPE::ASSIGN, ch);
        default:
            std::cerr << "Unknown TOKEN_TYPE @ " << line_num << " : " << ch << std::endl;
	  return lex();
    }
}
