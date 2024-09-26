#include "src/lexer.h"
#include "src/printer.h"

#include <iostream>
#include <fstream>

int main() {
    Reader md_reader("../test.md");
    std::string buffer = md_reader.read();
    
    Lexer lexer(buffer);
    lexer.scan_tokens();
    lexer.display_tokens();

    // Printer printer(lexer.tokens(), "../layout.html");
    // printer.print("../test.html");

    return 0;
}