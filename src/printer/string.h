// String str("Hello ");
// str.concat("World!");
// std::cout << str;
// deallocate resource
#define STRING_

#include <iostream>
#include <assert.h>
#include <errno.h>

unsigned int length(const char*);

void copy(void* dst, const void* src, const unsigned int n);

class String {
    unsigned int count;

    public:
        char *data;
        String();
        String(const char*);
        void concat(const char*);
        void concat(const String);
        unsigned int len();
        String operator+(const char* rhs);
        String operator+(const String rhs);
        ~String();
};