#include <iostream>
#include "Tools.hpp"

int main(){

    double degree = to_degree(to_radian(120));

    std::cout << degree << std::endl;

    return 0;
}