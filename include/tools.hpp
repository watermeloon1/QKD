#ifndef TOOLS_HPP
#define TOOLS_HPP

double to_radian(double degree);
double to_degree(double radian);
double zenit(double distance_to_earth, double distance_to_base);
double to_wavenumber(double wavelenght);
double beam_widening_vacuum(double link_distance, double telescope_aperture, double wavelenght);
double beam_widening_atmosphere(double link_distance, double telescope_aperture, double wavelenght, double coherence_length);
double turbulence_strength(double height_above_sea_level, double wind_speed = 21);

#endif