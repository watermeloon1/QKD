#include <iostream>
#include "../include/Tools.hpp"
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/Values.hpp"

#include<fstream>
#include <vector>

int main(){

    BB84 *q = new BB84(15000, 43);

    std::cout << q->get_protocol_name() << std::endl;

    std::vector<std::string> scenario;
    scenario.push_back("Midlatitude");
    scenario.push_back("Summer");
    scenario.push_back("Clear");

    q->set_climate(scenario[0]);
    q->set_season(scenario[1]);
    q->set_weather(scenario[2]);


    //for(int i = 0; i < q->distance_sections.size(); i++){
    //    std::cout << q->distance_sections[i] << std::endl;
    //}

    //std::vector<double> ms = q->get_molecular_scattering();
    //for(int i = 0; i < ms.size(); i++){
    //    std::cout << ms[i] << std::endl;
    //}

    q->cout_distance_sectors();
    std::cout << q->get_zenith() << std::endl;

    delete q;

    return 0;
}
