#include <iostream>
#include <math.h>
#include "../include/QProtocol.hpp"
#include "../include/values.hpp"

QProtocol::QProtocol(){

}

/**
 * @brief Assigns a vlaue to the distance variable, based on the height and the zenith.
 * 
 */
void QProtocol::set_distance(){

    double a, b, c, d;

    double h = this->height_above_sea_level;
    double z = this->zenith;

    a = sqrt(pow(EARTH_RADIUS, 2) * pow(cos(RADIAN(z)), 2));
    b = 2 * EARTH_RADIUS * h;
    c = pow(h, 2);
    d = EARTH_RADIUS * cos(RADIAN(z));

    distance =  a + b + c - d;
} 

/**
 * @brief Assigns values to the sections of the distance.
 * 
 */
void QProtocol::slice_distance(){


    distance_sections[0] = 0;

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
        if(distance_sections[i] > 60000){
            distance_sections[i + 1] = distance_sections[i] + 10000;
            continue;
        }
    }
}