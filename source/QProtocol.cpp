#include "../include/QProtocol.hpp"
#include "../include/values.hpp"

QProtocol::QProtocol(){
    init_loss();
    init_distance_sections();
}

/**
 * @brief Assigns a vlaue to the distance variable, based on the height and the zenith.
 * 
 */
void QProtocol::init_distance(){

    double a, b, c, d;

    double h = this->height_above_sea_level;
    double z = this->zenith;

    a = sqrt(pow(EARTH_RADIUS, 2) * pow(cos(RADIAN(z)), 2));
    b = 2 * EARTH_RADIUS * h;
    c = pow(h, 2);
    d = EARTH_RADIUS * cos(RADIAN(z));

    this->distance =  a + b + c - d;
} 

/**
 * @brief Divides the distance that the beam travels into sections.
 * 
 */
void QProtocol::init_distance_sections(){

    this->distance_sections.assign(50,0);

    for(int i = 0; i < distance_sections.size() - 1; i++){
        if(distance_sections[i] < 1000){
            distance_sections[i + 1] = distance_sections[i] + 200;
            continue;
        }
        if(distance_sections[i] < 30000){
            distance_sections[i + 1] = distance_sections[i] + 1000;
            continue;
        }
        if(distance_sections[i] < 60000){
            distance_sections[i + 1] = distance_sections[i] + 5000;
            continue;
        }
        if(distance_sections[i] >= 60000){
            distance_sections[i + 1] = distance_sections[i] + 10000;
            continue;
        }
    }
}

/**
 * @brief Initialises the vectors of scattering and absorption with layers
 * 
 */
void QProtocol::init_loss(){
    std::vector<double> aerosol_absorption(33,0);
    std::vector<double> aerosol_scattering(33,0); 
    std::vector<double> molecular_absorption(33,0);
    std::vector<double> molecular_scattering(33,0);
    std::vector<double> layers(33,0);
}

QProtocol::~QProtocol(){}