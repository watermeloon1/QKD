#include <iostream>
#include <math.h>
#include "../include/tools.hpp"

#define PI 3.14159265 
#define EARTH_RADIUS 6378

/**
 * @brief Converts degrees to radians.
 * 
 * @param degree double - the angle in degrees
 * @return double - the angle in radians
 */
double to_radian(double degree){
  return (degree*PI)/180;
}

/**
 * @brief Converts radians to degrees.
 * 
 * @param radian double - the angle in radians
 * @return double - the angle in degrees
 */
double to_degree(double radian){
  return (radian*180)/PI;
}

/**
 * @brief Converts kilometers to meters.
 * 
 * @param kilometer double - the distance in kilometers
 * @return double - the distance in meters
 */
double to_meter(double kilometer){
  return kilometer * 1000;
}

/**
 * @brief Calculates the zenit angle of the beam hitting/leaving the surface of Earth.
 * 
 * @param distance_to_earth double - the shortest distance between the sattelite and the surface of Earth (km)
 * @param distance_to_base double - the shortest distance between the sattelite and the communicating base (km)
 * @return double - the zenit angle ( °)
 */
double zenit(double distance_to_earth, double distance_to_base){

  if (distance_to_earth <= distance_to_base){

    double numerator, denominator, alfa_radian, alfa_degree, zenit_degree;

    numerator = pow(EARTH_RADIUS, 2) + pow(distance_to_base, 2) - pow(EARTH_RADIUS + distance_to_earth, 2);
    denominator = 2 * EARTH_RADIUS * distance_to_base;
    alfa_radian = acos(numerator/denominator);
    alfa_degree = to_degree(alfa_radian);
    zenit_degree = 180 - alfa_degree;

    return zenit_degree;

  } else { return -1; }
}

/**
 * @brief Converts the wavelength to a wavenumber, that can be used in the calculations.
 * 
 * @param wavelenght double - the wavelength of the beam, for the wavenumber (nm)
 * @return double - the wavenumber
 */
double to_wavenumber(double wavelenght){
  return 2 * PI / (wavelenght * pow(10, -9)); //gallium arsenide ??
}

/**
 * @brief The beam widening of a beam going through vacuum.
 * 
 * @param link_distance double - the distance between the emitter and the receiver (km)
 * @param telescope_aperture double - the aperture of the emitting telescope (m)
 * @param wavelenght double - the wavelength of the beam, for the wavenumber (nm)
 * @return double - the extent of the widening (m)
 */
double beam_widening_vacuum(double link_distance, double telescope_aperture, double wavelenght){

  double a, b, c;

  double wavenumber =  to_wavenumber(wavelenght);
  double link_distance_m = to_meter(link_distance);

  a = 4 * pow(link_distance, 2);
  b = pow(wavenumber, 2) * pow(telescope_aperture, 2);
  c = pow(telescope_aperture, 2);

  return sqrt(a/b + c/4);
}

/**
 * @brief The beam widening of a beam going through the atmosphere.
 * 
 * @param link_distance double - the distance between the emitter and the receiver (km)
 * @param telescope_aperture double - the aperture of the emitting telescope (m)
 * @param wavelenght double - the wavelength of the beam, for the wavenumber (nm)
 * @param coherence_length double - length of the coherence
 * @return double - the extent of the widening (m)
 */
double beam_widening_atmosphere(double link_distance, double telescope_aperture, double wavelenght, double coherence_length){

  double a, b, c, d, e, f;

  double wavenumber = to_wavenumber(wavelenght);
  double link_distance_m = to_meter(link_distance);

  a = 4 * pow(link_distance_m, 2);
  b = pow(wavenumber, 2) * pow(telescope_aperture, 2);
  c = pow(telescope_aperture, 2);
  d = 4 * pow(link_distance_m, 2);
  e = pow(wavenumber * coherence_length, 2);
  f = pow(1 - 0.62 * (pow(coherence_length / telescope_aperture, 1/3)), 6/5);

  return sqrt(a/b + c/4 + d/e * f);
}

/**
 * @brief The strength of the turbulence in the atmospheare of Earth.
 * 
 * @param height_above_sea_level double - the height of the observed object (km)
 * @param wind_speed double - the speed of the wind at the give height (m/s)
 * @return double - the strength of the turbulence
 */
double turbulence_strength(double height_above_sea_level, double wind_speed = 21){
  
  double a, b, c, d, e;

  double A = 1.7 * pow(10, -14);

  a = 0.00594 * pow((wind_speed / 27), 2);
  b = pow(height_above_sea_level * pow(10, -5), 10);
  c = exp(height_above_sea_level / -1000);
  d = 2.7 * pow(10, -6) * exp(height_above_sea_level / -1500);
  e = A * exp(height_above_sea_level / -100);

  return a * b * c + d + e;
}


