#ifndef PRINTER_
#define PRINTER_

#include "lexer.h"
#include "fs.h"

/// @brief HTMl printer for converting the tokenized markdown to HTML.
class Printer {
    std::vector<Token> _tokens;
    std::string _layout;

    public:
        Printer() = delete;
        Printer(std::vector<Token> tokens);
        Printer(std::vector<Token> tokens, const char* layout_path);
        ~Printer() = default;

        void print();
        void print(const char* filepath);
        void print(std::string filepath);

        std::string format_layout();
        std::string wrap_body();
        std::vector<std::string> wrap_nav(std::string brand = "Arktetra");    // todo: take brand value from command line
        std::vector<std::string> wrap_content();
        std::string wrap_paragraph(std::string paragraph);
        std::string wrap_heading_1(std::string heading);
        std::string wrap_heading_2(std::string heading);
        std::string wrap_heading_3(std::string heading);
        std::string wrap_heading_4(std::string heading);
        std::string wrap_heading_5(std::string heading);
        std::string wrap_heading_6(std::string heading);

        std::string tabify(std::string str);
};

#endif