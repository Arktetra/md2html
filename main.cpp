#include "src/lexer.h"

#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vec) {
    stream << "[";
    for (unsigned int i = 0; i < vec.size(); i++) {
        std::cout << vec[i];

        if (i != vec.size() - 1)
            stream << " ";
    }
    stream << "]";

    return stream;
}

int main() {
    Lexer lexer(
        "# Header1\n"
        "## Header2\n"
        "### Header3\n"
        "#### Header4\n"
        "##### Header5\n"
        "###### Header6\n"
        "####### Header7\n"
        "#####Header8\n"
    );
    lexer.scan_tokens();

    lexer.display_tokens();
    return 0;
}