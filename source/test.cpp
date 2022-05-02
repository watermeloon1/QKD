#include <iostream>
#include "../include/tools.hpp"

int main(){

    Tools tools;

    double zen = tools.zenith(1500, 1678);

    std::cout << zen << std::endl;

    return 0;
}