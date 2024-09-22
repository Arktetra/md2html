#ifndef FS_
#define FS_

#include <string>
#include <fstream>
#include <iostream>

class Reader {
    const char* _file_path;

    public:
        Reader() = default;
        Reader(const char* file_path) : _file_path(file_path) {}
        ~Reader() = default;

        std::string read();
};

class Writer {
    const char* _file_path;
    
    public:
        Writer() = default;
        Writer(const char* file_path) : _file_path(file_path) {}
        ~Writer() = default;

        void write(std::string buffer);
};

#endif