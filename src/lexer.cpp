#include "lexer.h"


std::ostream& operator<<(std::ostream& stream, const TokenType& type) {
    switch (type) {
        case TokenType::H1: return stream << "H1";
        case TokenType::H2: return stream << "H2";
        case TokenType::H3: return stream << "H3";
        case TokenType::H4: return stream << "H4";
        case TokenType::H5: return stream << "H5";
        case TokenType::H6: return stream << "H6";
        case TokenType::P: return stream << "P" ;
        case TokenType::eof: return stream << "eof";
        case TokenType::None: return stream << "None";
    }
    return stream << "None";
}

Token::Token(TokenType type, std::string lexeme) {
    this->_type = type;
    this->_lexeme = lexeme;
}

TokenType Token::type() {
    return this->_type;
}

std::string Token::lexeme() {
    return this->_lexeme;
}

std::ostream& operator<<(std::ostream& stream, Token& token) {
    stream << "Token {type: " << token.type() << ", lexeme: " << token.lexeme() << "}";
    return stream;
}

void Lexer::scan_tokens() {
    while (!this->is_at_end()) {
        this->start = this->current;
        this->scan_token();
    }

    _tokens.push_back(Token(TokenType::eof, ""));
}

void Lexer::scan_token() {
    char c = this->advance();

    switch (c) {
        case '#': heading();
    }
}

void Lexer::heading() {
    char c = this->advance();
    unsigned int heading_level_counter = 1;
    
    while (c == '#') {
        heading_level_counter += 1;
        c = this->advance();
    }

    if (c != ' ') error("Expected a ' ' after header tag.");

    unsigned int lexeme_start = this->current;

    while (c != '\n' && !this->is_at_end()) {
        c = this->advance();
    }

    unsigned int lexeme_size = this->current - lexeme_start;
    unsigned int lexeme_iterator;
    unsigned int source_iterator;

    char* lexeme = new char [lexeme_size];

    for (
        lexeme_iterator = 0, source_iterator = lexeme_start; 
        source_iterator != this->current; 
        lexeme_iterator++, source_iterator++
    ) {
        if (source[source_iterator] != '\n')
            lexeme[lexeme_iterator] = source[source_iterator];
    }

    lexeme[lexeme_iterator] = '\0';

    std::string header = (const char*) lexeme;
    delete[] lexeme;
    _tokens.push_back(Token(this->heading_level(heading_level_counter), header));
    }

TokenType Lexer::heading_level(unsigned int heading_level_counter) {
    switch (heading_level_counter) {
        case 1: return TokenType::H1;
        case 2: return TokenType::H2;
        case 3: return TokenType::H3;
        case 4: return TokenType::H4;
        case 5: return TokenType::H5;
        default: return TokenType::H6;
    }
}

char Lexer::advance() {
    char c = source[current];
    current += 1;
    return c;
}

bool Lexer::is_at_end() {
    return this->current >= this->source.length();
}

void Lexer::error(const char* message) {
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}

void Lexer::display_tokens() {
    for (unsigned int i = 0; i < this->_tokens.size(); i++) {
        std::cout << this->_tokens[i] << std::endl;
    }
}

std::vector<Token> Lexer::tokens() {
    return _tokens;
}