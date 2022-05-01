#include <iostream>
#include <math.h>
#include "Tools.hpp"

#define PI 3.14159265 
#define EARTH_RADIUS 6378

double to_radian(double degree){
  return (degree*PI)/180;
}

double to_degree(double radian){
  return (radian*180)/PI;
}

double zenit(double distance_to_earth, double distance_to_base){

  double numerator, denominator, alfa_radian, alfa_degree, zenit_degree;

  numerator = pow(EARTH_RADIUS, 2) + pow(distance_to_base, 2) - pow(EARTH_RADIUS + distance_to_earth, 2);
  denominator = 2 * EARTH_RADIUS * distance_to_base;

  alfa_radian = acos(numerator/denominator);
  alfa_degree = to_degree(alfa_radian);

  zenit_degree = 180 - alfa_degree;

  return zenit_degree;
}

