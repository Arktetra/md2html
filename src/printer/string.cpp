#include "./string.h"

namespace Utils {
    unsigned int length(const char* str) {
        unsigned int i;
        const char *p;

        for (i = 0, p = str; *p; i++, p++);

        return i;
    }

    void copy(void* dst, const void* src, int count) {
        const char* psrc;
        char* pdst;

        for (psrc = (const char*)src, pdst = (char*)dst;
            count; 
            psrc++, pdst++, count--) {
            *pdst = *psrc;
        }

        *pdst = '\0';

    }
}

String::String(const char* str) {
    size = Utils::length(str);
    ptr = UniquePtr<const char>(str);
}

String::String(String&& str) {
    this->size = str.len();
    this->ptr = std::move(str.ptr);
}

String& String::operator=(String&& o) {  
    this->size = o.size;
    this->ptr = std::move(o.ptr);

    return *this;
}

void String::concat(const char* str) {
    this->check_nullptr("the original string");

    const char* lhs = this->ptr.release();
    unsigned int str_size = Utils::length(str);
    unsigned int new_size = this->size + str_size;

    char* new_data_ptr = new char;
    Utils::copy(new_data_ptr, lhs, this->size);
    Utils::copy(new_data_ptr + this->size, str, new_size);

    this->size = new_size;
    this->ptr = UniquePtr<const char>(new_data_ptr);
}

String String::operator+(const char* str) {
    this->check_nullptr("the original string");

    const char* lhs = this->ptr.get();

    unsigned int str_size = Utils::length(str);
    unsigned int new_size = this->size + str_size;
    
    char* new_data_ptr = new char;
    Utils::copy(new_data_ptr, lhs, this->size);
    Utils::copy(new_data_ptr + this->size, str, new_size);

    return String((const char*)new_data_ptr);
}

String String::operator+(String& rhs) {
    this->check_nullptr("lhs");
    rhs.check_nullptr("rhs");
    
    return *this + rhs.get();
}

String String::copy() {
    this->check_nullptr("the string");
    
    char* new_data_ptr = new char;

    Utils::copy(new_data_ptr, this->get(), this->size);

    return String((const char*)new_data_ptr);
}

unsigned int String::len() {
    return this->size;
}

const char* String::get() {
    check_nullptr("string");

    return ptr.get();
}

/// For checking whether the data pointer of a string is a null pointer
/// or not, and displaying an error message if it evaluates to true.
void String::check_nullptr(const char* position) {
    if (this->ptr.get() == nullptr) {
        std::cerr << "Error: Data pointer of " << position << " is a null pointer.\n"
                     "       May be a move was performed on " << position << "." << std::endl;
        exit(139); 
    }
}

std::ostream& operator<<(std::ostream& stream, String& str) {
    stream << str.get();
    return stream;
}

String operator+(const char* lhs, String& rhs) {
    if (rhs.get() == nullptr) {
        std::cerr << "Error: Data pointer of rhs is a null pointer.\n"
                     "       May be the value has moved out of it." << std::endl;
    }

    unsigned int lhs_size = Utils::length(lhs);
    unsigned int new_size = lhs_size + rhs.len();

    char* new_data_ptr = new char;
    Utils::copy(new_data_ptr, lhs, lhs_size);
    Utils::copy(new_data_ptr + lhs_size, rhs.get(), new_size);

    return String((const char*)new_data_ptr);
}