#ifndef STRING_
#define STRING_

#include <iostream>
#include "../memory/unique_ptr.h"

namespace Utils {
    unsigned int length(const char* str);
    void copy(void* dst, void* src, int count);
}

class String {
    unsigned int size;
    UniquePtr<const char> ptr;

    public:
        String() : size(0), ptr(nullptr) {}
        String(const char*);
        String(String&&);
        ~String() = default;

        String& operator=(String&&);

        void concat(const char*);

        String operator+(const char*);
        String operator+(String&);

        String copy();
        
        unsigned int len();

        const char* get();

        void check_nullptr(const char* position);
};

std::ostream& operator<<(std::ostream& stream, String& str);
String operator+(const char* lhs, String& rhs);

#endif