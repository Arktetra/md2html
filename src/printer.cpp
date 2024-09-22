#include "printer.h"

/// Initiates printer by taking the tokens from the lexer.
/// # Example
/// ```c++
/// Reader md_reader("../test.md");
/// std::string buffer = md_reader.read();
///  
/// Lexer lexer(buffer);
/// lexer.scan_tokens();
///
/// Printer printer(lexer.tokens());
/// printer.print("../test.html");
/// ```
Printer::Printer(std::vector<Token> tokens) {
    this->_tokens = tokens;

    this->_layout = "<!DOCTYPE html>\n"
                    "<html lang = \"en\">\n"
                    "<head>\n"
                    "   <meta charset = \"UTF-8\">\n"
                    "   <meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\">\n"
                    "   <title>Document</title>\n"
                    "</head>\n"
                    "{}\n"
                    "</html>";
}

/// Initiates printer by taking the tokens from the lexer and a path
/// to the HTML layout.
/// # Example
/// ```c++
/// Reader md_reader("../test.md");
/// std::string buffer = md_reader.read();
///  
/// Lexer lexer(buffer);
/// lexer.scan_tokens();
///
/// Printer printer(lexer.tokens(), "../layout.html");
/// printer.print("../test.html");
/// ```
Printer::Printer(std::vector<Token> tokens, const char* layout_path) {
    this->_tokens = tokens;

    Reader layout_reader(layout_path);
    this->_layout = layout_reader.read();
}

void Printer::print() {
    std::cout << this->_layout + this->wrap_body();
}

void Printer::print(const char* file_path) {
    Writer html_printer(file_path);

    html_printer.write(this->format_layout());
}

void Printer::print(std::string file_path) {
    this->print(file_path.c_str());
}

std::string Printer::format_layout() {
    std::string body = wrap_body();

    char* formatted_layout_ptr = new char [this->_layout.length() + body.length() - 2 + 1];
    unsigned int formatted_layout_iter;
    unsigned int layout_iter;
    unsigned int body_iter;

    for (
        formatted_layout_iter = 0, layout_iter = 0;
        this->_layout[layout_iter] != '{';
        formatted_layout_iter++, layout_iter++
    ) {
        formatted_layout_ptr[formatted_layout_iter] = this->_layout[layout_iter];
    }

    for (
        body_iter = 0;
        body_iter < body.length();
        formatted_layout_iter++, body_iter++
    ) {
        formatted_layout_ptr[formatted_layout_iter] = body[body_iter];
    }

    for (
        layout_iter += 2;
        layout_iter < this->_layout.length();
        formatted_layout_iter++, layout_iter++
    ) {
        formatted_layout_ptr[formatted_layout_iter] = this->_layout[layout_iter];
    }

    formatted_layout_ptr[formatted_layout_iter] = '\0';

    std::string formatted_layout = (const char*) formatted_layout_ptr;
    delete [] formatted_layout_ptr;

    return formatted_layout;
}

std::string Printer::wrap_body() {
    std::string body = "";

    std::vector<std::string> nav_buffer = wrap_nav();
    std::vector<std::string> content_buffer = wrap_content();

    for (unsigned int i = 0; i < nav_buffer.size(); i++) {
        body += tabify(nav_buffer[i]) + "\n";
    }

    for (unsigned int i = 0; i < content_buffer.size(); i++) {
        body += tabify(content_buffer[i]) + "\n";
    }

    return "<body>\n" + body + "</body>";
}

std::vector<std::string> Printer::wrap_nav(std::string brand) {
    std::vector<std::string> nav_buffer;

    nav_buffer.push_back("<nav>");
    nav_buffer.push_back(tabify(wrap_heading_1(brand)));
    nav_buffer.push_back("</nav>");
    nav_buffer.push_back("<hr>");

    return nav_buffer;
}

std::vector<std::string> Printer::wrap_content() {
    std::vector<std::string> content_buffer;
    content_buffer.push_back("<div class = \"content\">");
    
    for (unsigned int i = 0; i < _tokens.size(); i++) {
        switch (_tokens[i].type()) {
            case TokenType::P:
                content_buffer.push_back(tabify(wrap_paragraph(_tokens[i].lexeme())));
                break;
            case TokenType::H1:
                content_buffer.push_back(tabify(wrap_heading_1(_tokens[i].lexeme())));
                break;
            case TokenType::H2:
                content_buffer.push_back(tabify( wrap_heading_2(_tokens[i].lexeme())));
                break;
            case TokenType::H3:
                content_buffer.push_back(tabify(wrap_heading_3(_tokens[i].lexeme())));
                break;
            case TokenType::H4:
                content_buffer.push_back(tabify(wrap_heading_4(_tokens[i].lexeme())));
                break;
            case TokenType::H5:
                content_buffer.push_back(tabify(wrap_heading_5(_tokens[i].lexeme())));
                break;
            case TokenType::H6:
                content_buffer.push_back(tabify(wrap_heading_6(_tokens[i].lexeme())));
                break;
            default:
                break;
        }
    }

    content_buffer.push_back("</div>");
    content_buffer.push_back("<hr>");

    return content_buffer;
}

std::string Printer::wrap_paragraph(std::string paragraph) {
    return "<p>" + paragraph + "</p>";
}

std::string Printer::wrap_heading_1(std::string heading) {
    return "<h1>" + heading + "</h1>";
}

std::string Printer::wrap_heading_2(std::string heading) {
    return "<h2>" + heading + "</h2>";
}

std::string Printer::wrap_heading_3(std::string heading) {
    return "<h3>" + heading + "</h3>";
}

std::string Printer::wrap_heading_4(std::string heading) {
    return "<h4>" + heading + "</h4>";
}

std::string Printer::wrap_heading_5(std::string heading) {
    return "<h5>" + heading + "</h5>";
}

std::string Printer::wrap_heading_6(std::string heading) {
    return "<h6>" + heading + "</h6>";
}

std::string Printer::tabify(std::string str) {
    return "    " + str;
} 