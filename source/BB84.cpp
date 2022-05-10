#include <iostream>
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

	std::cout << "benne" << std::endl;
	Tools *tools = new Tools();
	std::cout << "benne" << std::endl;
	
	std::cout << "this.dir" << this -> direction << std::endl;
	switch (this -> direction)
	{
	std::cout << "benne" << std::endl;
	
	case 0:
		static_loss = tools->static_loss(molecular_scattering, molecular_absorption, aerosol_scattering, aerosol_absorption, layers, zenith);
		coherence_length = tools->beam_widening_earth_space(wave_length, distance_sectors, distance, windspeed, zenith);
		beam_widening = tools->beam_widening_atmosphere(distance, wave_length, coherence_length, aperture_diameter);
		targeting_error = tools->targeting_error(distance, targeting_angular_error);
		total_scattering = tools->total_scattering(beam_widening, targeting_error);
		dynamic_loss = tools->dynamic_loss(total_scattering, mirror_diameter / 2);
		
		break;

	case SPACE_EARTH:
		static_loss = tools->static_loss(molecular_scattering, molecular_absorption, aerosol_scattering, aerosol_absorption, layers, zenith);
		coherence_length = tools->beam_widening_space_earth(wave_length, distance_sectors, distance, windspeed, zenith);
		beam_widening = tools->beam_widening_atmosphere(distance, wave_length, coherence_length, aperture_diameter);
		targeting_error = tools->targeting_error(distance, targeting_angular_error);
		total_scattering = tools->total_scattering(beam_widening, targeting_error);
		dynamic_loss = tools->dynamic_loss(total_scattering, mirror_diameter / 2);
		break;

	case SPACE_SPACE:
		static_loss = 1;
		beam_widening = tools->beam_widening_vacuum(space_space_channel_length, wave_length, aperture_diameter);
		targeting_error = tools->targeting_error(space_space_channel_length, targeting_angular_error);
		total_scattering = tools->total_scattering(beam_widening, targeting_error);
		dynamic_loss = tools->dynamic_loss(total_scattering, mirror_diameter / 2);
		break;
	}

	delete tools;

	transmittance = static_loss * dynamic_loss;
	qber_value = probability_of_polarization_measurement_error + ((noise * number_of_detectors) / (transmittance * mean_photon_number_of_signal * quantum_efficiency_of_detector * 2));
}

double BB84::get_qber()
{
	return this -> qber_value;
}

BB84::BB84(double height_above_sea_level, double distance) : QProtocol(height_above_sea_level, distance) {}
BB84::~BB84() {}
