#ifndef TOOLS_HPP
#define TOOLS_HPP

class Tools{  
    public:  
 
        double zenith(double distance_to_earth, double distance_to_base);

        double beam_widening_vacuum(double link_distance, double telescope_aperture, double wavelenght);

        double beam_widening_atmosphere(double link_distance, double telescope_aperture, double wavelenght, double coherence_length);

        double turbulence_strength(double height_above_sea_level, double wind_speed = 21);

        double targeting_error(double link_distance, double angular_error);

        double total_scattering(double beam_radius, double targeting_error);

        double dynamic_loss(double total_scattering, double mirror_radius);

        double static_loss(std::vector <double> molecular_scattering, std::vector <double> molecular_absorption, std::vector <double> aerosol_scattering, std::vector <double> aerosol_absorption, std::vector <double> layers_of_air, double zenith);

        double beam_widening_earth_space(double wave_length, std::vector<double> sectors, double distance, double wind_speed, double zenith);

        double beam_widening_space_earth(double wave_length, std::vector<double> sectors, double distance, double wind_speed, double zenith);

};

#endif
