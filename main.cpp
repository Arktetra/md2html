#include "src/lexer.h"

#include <iostream>
#include <fstream>

int main() {
    std::string str;
    std::string buffer = "";
    std::ifstream md_file("../test.md");

    if (!md_file.is_open()) {
        std::cerr << "Error: opening file" << std::endl;
    }

    while (std::getline(md_file, str)) {
        buffer += str + "\n";
    }
    
    Lexer lexer(buffer);
    lexer.scan_tokens();
    lexer.display_tokens();

    return 0;
}