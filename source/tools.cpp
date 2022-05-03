#include <iostream>
#include <math.h>
#include <vector>
#include "../include/tools.hpp"
#include "../include/values.hpp"

/**
 * @brief Calculates the zenit angle of the beam hitting/leaving the surface of Earth.
 * 
 * @param distance_to_earth double - the shortest distance between the sattelite and the surface of Earth (km)
 * @param distance_to_base double - the shortest distance between the sattelite and the communicating base (km)
 * @return double - the zenit angle ( °)
 */
double Tools::zenith(double distance_to_earth, double distance_to_base){

  if (distance_to_earth <= distance_to_base){

    double numerator, denominator, alfa_radian, alfa_degree, zenith_degree;

    numerator = pow(EARTH_RADIUS, 2) + pow(distance_to_base, 2) - pow(EARTH_RADIUS + distance_to_earth, 2);
    denominator = 2 * EARTH_RADIUS * distance_to_base;
    alfa_radian = acos(numerator / denominator);
    alfa_degree = DEGREE(alfa_radian);
    zenith_degree = 180 - alfa_degree;

    return zenith_degree;

  } else { return -1; }
}

/**
 * @brief The beam widening of a beam going through vacuum.
 * 
 * @param link_distance double - the distance between the emitter and the receiver (km)
 * @param telescope_aperture double - the aperture of the emitting telescope (m)
 * @param wavelenght double - the wavelength of the beam, for the wavenumber (nm)
 * @return double - the extent of the widening (m)
 */
double Tools::beam_widening_vacuum(double link_distance, double telescope_aperture, double wavelenght){

  double a, b, c;

  double wavenumber =  WAVE(wavelenght);
  double link_distance_m = METER(link_distance);

  a = 4 * pow(link_distance, 2);
  b = pow(wavenumber, 2) * pow(telescope_aperture, 2);
  c = pow(telescope_aperture, 2);

  return sqrt(a / b + c / 4);
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
double Tools::beam_widening_atmosphere(double link_distance, double telescope_aperture, double wavelenght, double coherence_length){

  double a, b, c, d, e, f;

  double wavenumber = WAVE(wavelenght);
  double link_distance_m = METER(link_distance);

  a = 4 * pow(link_distance_m, 2);
  b = pow(wavenumber, 2) * pow(telescope_aperture, 2);
  c = pow(telescope_aperture, 2);
  d = 4 * pow(link_distance_m, 2);
  e = pow(wavenumber * coherence_length, 2);
  f = pow(1 - 0.62 * (pow(coherence_length / telescope_aperture, 1 / 3)), 6 / 5);

  return sqrt(a / b + c / 4 + d / e * f);
}

/**
 * @brief The strength of the turbulence in the atmospheare of Earth.
 * 
 * @param height_above_sea_level double - the height of the observed object (km)
 * @param wind_speed double - the speed of the wind at the give height (m/s)
 * @return double - the strength of the turbulence
 */
double Tools::turbulence_strength(double height_above_sea_level, double wind_speed){
  
  double a, b, c, d, e;

  double A = 1.7 * pow(10, -14);

  a = 0.00594 * pow((wind_speed / 27), 2);
  b = pow(height_above_sea_level * pow(10, -5), 10);
  c = exp(height_above_sea_level / -1000);
  d = 2.7 * pow(10, -6) * exp(height_above_sea_level / -1500);
  e = A * exp(height_above_sea_level / -100);

  return a * b * c + d + e;
}

/**
 * @brief Calculates the targeting error of the beam.
 * 
 * @param link_distance double - the distance between the emitter and the receiver (km)
 * @param angular_error double - the deviation from the optimal direction (μrad)
 * @return double - the deviation from the receiver (m)
 */
double Tools::targeting_error(double link_distance, double angular_error){

  double a,b;

  double link_distance_m = METER(link_distance);

  a = link_distance_m * angular_error;
  b = pow(10, -6);

  return a * b;
}

/**
 * @brief The total scattering of the beam.
 * 
 * @param beam_radius double - the radius of the mitted beam
 * @param targeting_error double - the targeting error of the beam (m)
 * @return double - the total scattering of the beam (m)
 */
double Tools::total_scattering(double beam_radius, double targeting_error){

  double a, b;

  a = sqrt(pow(beam_radius, 2));
  b = pow(targeting_error, 2);

  return a + b;
}

/**
 * @brief Calculates the dynamic loss of the channel.
 * 
 * @param total_scattering double - the total scattering of the beam (m)
 * @param mirror_radius double - the mirror radius of the receiver (m)
 * @return double - the total dynamic loss of the channel
 */
double Tools::dynamic_loss(double total_scattering, double mirror_radius){

  double a, b;

  a = (-1) * pow(mirror_radius, 2);
  b = 2 * pow(total_scattering, 2);

  return 1 - exp(a / b);
}

/**
 * @brief Calculates the static loss of the beam going through the atmosphere of Earth.
 * 
 * @param molecular_scattering vector <double> - the molecular scattering of the beam due to climate conditions
 * @param molecular_absorption vector <double> - the molecular absorption of the atmosphere
 * @param aerosol_scattering vector <double> - the molecular scattering of the beam due to weather conditions
 * @param aerosol_absorption vector <double> - the aerosol absorption of the atmosphere
 * @param layers_of_air vector <double> - the atmosphere of Earth divided to several layers on top of each other
 * @param zenith double - the zenith angle of the beam 
 * @return double - the sum of the static loss in all of the individual layers
 */
double Tools::static_loss(std::vector <double> molecular_scattering, std::vector <double> molecular_absorption, 
  std::vector <double> aerosol_scattering, std::vector <double> aerosol_absorption, std::vector <double> layers_of_air, double zenith){

  std::vector <double> scattering(molecular_scattering.size());

  for(int i; i < molecular_scattering.size(); i++){
    scattering[i] = molecular_scattering[i] + aerosol_scattering[i];
  }

  std::vector <double> absorption(molecular_absorption.size());

  for(int i; i < molecular_absorption.size(); i++){
    absorption[i] = molecular_absorption[i] + aerosol_absorption[i];
  }

  double sum_of_layers = 0;

  for(int i; i < layers_of_air.size(); i++){
    sum_of_layers = sum_of_layers + (((scattering[i] + scattering[i + 1]) / 2) + ((absorption[i] + absorption[i + 1]) / 2)) *
      ((layers_of_air[i + 1] - layers_of_air[i]) / cos(zenith * (PI / 180))); 
  }

  return exp((-1) * sum_of_layers);
}