#ifndef LEXER_
#define LEXER_

#include <vector>
#include <string>
#include <iostream>

enum class TokenType {
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    P,
    Next,
    Prev,
    eof,
    None
};

std::ostream& operator<<(std::ostream& stream, const TokenType& type);

class Token {
    std::string _lexeme;
    TokenType _type;

    public:
        Token() : _lexeme(""), _type(TokenType::None) {}
        Token(TokenType type, std::string lexeme);
        ~Token() = default;

        TokenType type();
        std::string lexeme();

};

std::ostream& operator<<(std::ostream& stream, Token& token);

class Lexer {
    unsigned int current;
    unsigned int start;
    std::string source;
    std::vector<Token> _tokens;

    public:
        Lexer(std::string source) : current(0), source(source) {}
        ~Lexer() = default;

        void scan_tokens();
        void scan_token();
        void heading();
        void paragraph();
        void next();
        void previous();
        TokenType heading_level(unsigned int heading_level_counter);
        char advance();
        char peek();
        char peek_next();
        bool is_at_end();

        void error(const char* message);
        void display_tokens();
        std::string slice_source(unsigned int begin, unsigned int end);
        std::vector<Token> tokens();
        
};

#endif