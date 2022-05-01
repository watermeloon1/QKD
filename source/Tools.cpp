#include <iostream>
#include <math.h>
#include "../include/tools.hpp"

#define PI 3.14159265 
#define EARTH_RADIUS 6378

double to_radian(double degree){
  return (degree*PI)/180;
}

double to_degree(double radian){
  return (radian*180)/PI;
}

double zenit(double distance_to_earth, double distance_to_base){

  if (distance_to_earth <= distance_to_base){

    double numerator, denominator, alfa_radian, alfa_degree, zenit_degree;

    numerator = pow(EARTH_RADIUS, 2) + pow(distance_to_base, 2) - pow(EARTH_RADIUS + distance_to_earth, 2);
    denominator = 2 * EARTH_RADIUS * distance_to_base;

    alfa_radian = acos(numerator/denominator);
    alfa_degree = to_degree(alfa_radian);

    zenit_degree = 180 - alfa_degree;

    return zenit_degree;

  }else{ return -1; }
}

double to_wavenumber(double wavelenght){
  return 2 * PI / (wavelenght * pow(10, -9)); //gallium arsenide ??
}

double beam_widening_vacuum(double link_distance, double telescope_aperture, double wavelenght){

  double wavenumber =  to_wavenumber(wavelenght);
  //link_distance *= 1000; ??
  return sqrt(4 * pow(link_distance, 2) / (pow(wavenumber, 2) * pow(telescope_aperture, 2)) + pow(telescope_aperture, 2) / 4);
}

double beam_widening_atmosphere(double link_distance, double telescope_aperture, double wavelenght, double coherence_length){

  double wavenumber = to_wavenumber(wavelenght);

  return sqrt(4 * pow(link_distance, 2) / (pow(wavenumber, 2) * pow(telescope_aperture, 2)) + pow(telescope_aperture, 2) / 4 + 
    4 * pow(link_distance, 2) / pow(wavenumber * coherence_length, 2) * pow(1 - 0.62 * (pow(coherence_length / telescope_aperture, 1/3)), 6/5));





}

