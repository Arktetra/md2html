#include "fs.h"

std::string Reader::read() {
    std::string str;
    std::string buffer = "";
    std::ifstream input_file(_file_path);

    if (!input_file.is_open()) {
        std::cerr << "Error: opening file '" << _file_path << "'" << std::endl;
        exit(127);
    }

    while (std::getline(input_file, str)) {
        buffer += str + "\n";
    }

    input_file.close();

    return buffer;
}

void Writer::write(std::string buffer) {
    std::ofstream output_file(_file_path);

    if (!output_file.is_open()) {
        std::cerr << "Error: opening file '" << _file_path << "'" << std::endl;
        exit(127);
    }

    output_file << buffer;

    output_file.close();
}