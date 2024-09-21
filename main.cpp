#include <iostream>
#include "src/printer/string.h"

int main() {
    String str_a = String("alpha");
    String str_b = String("beta");
    String str_c = String("gamma");

    String str_d = str_a + "hmmm";
    String str_e = str_a + str_d;
    String str_f = "hmmm" + str_a;

    std::cout << str_d.len() << ": " << str_d << std::endl;
    std::cout << str_e.len() << ": " << str_e << std::endl;
    std::cout << str_f.len() << ": " << str_f << std::endl;
    std::cout << str_d.len() << ": " << str_d << std::endl;
    std::cout << str_a.len() << ": " << str_a << std::endl;

    return 0;
}