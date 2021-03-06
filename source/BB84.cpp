#include <iostream>
#include <iomanip>
#include "../include/Values.hpp"
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/Tools.hpp"

/**
 * @brief Pure virtual function redefinition in derived class.
 *
 * @return std::string - the name of the protocol
 */
std::string BB84::get_protocol_name()
{
	return "BB84";
}

/**
 * @brief Calculates the QBER value of the channel.
 *
 */
void BB84::qber()
{
	
	switch (this -> direction)
	{
	
	case EARTH_SPACE:
		static_loss = Tools::static_loss(molecular_scattering, molecular_absorption, aerosol_scattering, aerosol_absorption, layers, zenith);
		coherence_length = Tools::beam_widening_earth_space(wave_length, distance_sectors, distance, wind_speed, zenith);
		beam_widening = Tools::beam_widening_atmosphere(distance, aperture_diameter,wave_length, coherence_length);
		targeting_error = Tools::targeting_error(distance, targeting_angular_error);
		total_scattering = Tools::total_scattering(beam_widening, targeting_error);
		dynamic_loss = Tools::dynamic_loss(total_scattering, mirror_diameter / 2);
		
		break;

	case SPACE_EARTH:
		static_loss = Tools::static_loss(molecular_scattering, molecular_absorption, aerosol_scattering, aerosol_absorption, layers, zenith);
		coherence_length = Tools::beam_widening_space_earth(wave_length, distance_sectors, distance, wind_speed, zenith);
		beam_widening = Tools::beam_widening_atmosphere(distance, aperture_diameter,wave_length, coherence_length);
		targeting_error = Tools::targeting_error(distance, targeting_angular_error);
		total_scattering = Tools::total_scattering(beam_widening, targeting_error);
		dynamic_loss = Tools::dynamic_loss(total_scattering, mirror_diameter / 2);
		break;

	case SPACE_SPACE:
		static_loss = 1;
		beam_widening = Tools::beam_widening_vacuum(space_space_channel_length, wave_length, aperture_diameter);
		targeting_error = Tools::targeting_error(space_space_channel_length, targeting_angular_error);
		total_scattering = Tools::total_scattering(beam_widening, targeting_error);
		dynamic_loss = Tools::dynamic_loss(total_scattering, mirror_diameter / 2);
		break;
	}

	transmittance = static_loss * dynamic_loss;
	qber_value = probability_of_polarization_measurement_error + ((noise * number_of_detectors) / (transmittance * mean_photon_number_of_signal * quantum_efficiency_of_detector * 2));
}

BB84::BB84(double height_above_sea_level, double distance): QProtocol(height_above_sea_level, distance){
	
	qber();
	std::cout << std::fixed << std::setprecision(6);
	std::cout << "Static loss\t\t" << this->static_loss << std::endl; 
	std::cout << "Coherence length:\t" << this->coherence_length << std::endl;
	std::cout << "Beam widening:\t\t" << this->beam_widening << std::endl; 
	std::cout << "Targeting error:\t" << this->targeting_error << std::endl;
	std::cout << "Dynamic loss:\t\t" << this->dynamic_loss << std::endl;
	std::cout << "Transmittence:\t\t" << this->transmittance << std::endl;
	std::cout << "QBER:\t\t\t" << this->qber_value << std::endl;

}
BB84::~BB84() = default;
