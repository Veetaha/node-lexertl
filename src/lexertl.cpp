#include <iostream>
#include <cstdio>
#include <boost/numeric/conversion/cast.hpp>

#include <lexertl/runtime_error.hpp>

int main() {
    std::cout << boost::numeric_cast<int>(8000.0f);
    std::cout << fmt::format("Hello {} its {} number!!", "man", 8888) << std::endl;
    printf("HELLO WORLD!\n");
    return 0;
}
