#include <iostream>
#include "../include/tools.hpp"
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/values.hpp"

int main(){
    
    std::vector<double> asd;

    for(double i = 0; i < 30; i++){
        asd.push_back(i);
        std::cout << asd[i] << std::endl;
    }

    BB84 *q = new BB84;

    std::cout << q->get_protocol_name() << std::endl;

    for(int i = 0; i < q->distance_sections.size(); i++){
        std::cout << q->distance_sections[i] << std::endl;
    }

    delete q;

    return 0;
}