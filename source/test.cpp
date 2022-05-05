#include <iostream>
#include "../include/tools.hpp"
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/values.hpp"

#include<fstream>
#include <vector>


int main(){

    BB84 *q = new BB84;

    std::cout << q->get_protocol_name() << std::endl;

    std::vector<std::string> scenario;
    scenario.push_back("Midlatitude");
    scenario.push_back("Summer");
    scenario.push_back("Clear");

    q->set_climate(scenario[0]);
    q->set_season(scenario[1]);
    q->set_weather(scenario[2]);

    q->read_from_file();

    std::vector<double> ms = q->get_molecular_scattering();

    //for(int i = 0; i < q->distance_sections.size(); i++){
    //    std::cout << q->distance_sections[i] << std::endl;
    //}

    for(int i = 0; i < ms.size(); i++){
        std::cout << ms[i] << std::endl;
    }

    delete q;

    return 0;
}