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
        case '#': this->heading(); break;
        case '\n': this->advance(); break;
        default: this->paragraph();
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

    this->start = this->current;

    while (this->peek() != '\n' && !this->is_at_end()) {
        c = this->advance();
    }

    std::string header = this->slice_source(this->start, this->current);
    _tokens.push_back(Token(this->heading_level(heading_level_counter), header));
}

void Lexer::paragraph() {
    while (true) {
        if ((this->peek() == '\n' && this->peek_next() == '\n') 
            || (this->source.length() - this->current < 2)) {
            break;
        }

        this->advance();
    }

    std::string para = this->slice_source(this->start, this->current);
    _tokens.push_back(Token(TokenType::P, para));
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
    char c = source[this->current];
    this->current += 1;
    return c;
}

char Lexer::peek() {
    char c = source[this->current];
    return c;
}

char Lexer::peek_next() {
    try {
        if (this->current + 1 > source.length()) {
            throw "peeked out of bound value";
        }
        char c = source[this->current + 1];
        return c;
    } catch (const char* error) {
        throw error;
    }
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

/// @brief  returns `source[begin, end)`
/// @param begin 
/// @param end 
/// @return std::string
std::string Lexer::slice_source(unsigned int begin, unsigned int end) {
    if (begin >= end) 
        error("The beginning of the sliced string should be less than its end.");

    char* sliced_ptr = new char [end - begin + 1];
    unsigned int slice_iterator;
    unsigned int source_iterator;

    for (
        slice_iterator = 0, source_iterator = begin;
        source_iterator != end;
        slice_iterator++, source_iterator++
    ) {
        sliced_ptr[slice_iterator] = source[source_iterator];
    }

    sliced_ptr[slice_iterator] = '\0';

    std::string sliced_str = (const char*) sliced_ptr;

    delete [] sliced_ptr;

    return sliced_str;
}

std::vector<Token> Lexer::tokens() {
    return _tokens;
}