#include "./string.h"

unsigned int length(const char* str) {
    int n;
    const char *p;

    for (n = 0, p = str; *p; p++, n++);

    return n;
}

void copy(void* dst, const void* src, const unsigned int n) {
    const char *psrc;
    char *pdst;
    unsigned int i;

    for (i = n, psrc = (const char*)src, pdst = (char*)dst; i; psrc++, pdst++, i--) {
        *pdst = *psrc;
    }

    *pdst = '\0';

    return;
}

String::String() {
    this->count = 0;
    this->data = (char*)malloc(0);
}


String::String(const char* str) {
    this->count = length(str);
    this->data = (char*)malloc((this->count + 1) * sizeof(char));
    copy(this->data, str, this->count);
}

unsigned int String::len() {
    return this->count;
}

void String::concat(const char* str) {
    unsigned int str_len;
    str_len = length(str);
    this->data = (char*)realloc(this->data, (this->count + str_len + 1) * sizeof(char));
    copy(this->data + this->count, str, this->count + str_len);
}

void String::concat(const String str) {
    this->concat(str.data);
}

String String::operator+(const char* rhs) {
    unsigned int rhs_len = length(rhs);
    unsigned int lhs_len = this->len();

    char* result_data = (char*)malloc((lhs_len + rhs_len + 1) * sizeof(char));
    copy(result_data, this->data, lhs_len);
    copy(result_data + lhs_len, rhs, rhs_len);

    return String(result_data);
}

String String::operator+(const String rhs) {
    return String(*this + rhs.data);
}

String::~String() {
    free(this->data);
}