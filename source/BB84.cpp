#include <iostream>
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/values.hpp"
#include "../include/tools.hpp"

std::string BB84::get_protocol_name(){
    return "BB84";
}

void BB84::set_qber(){

    Tools *tools = new Tools();

    switch (direction){

    case EARTH_SPACE:
        static_loss = tools -> static_loss(molecular_scattering, molecular_absorption, aerosol_scattering, aerosol_absorption, layers, zenith);
        //coherence_length
        beam_widening = tools -> beam_widening_atmosphere(distance, wave_length, coherence_length, aperture_diameter);
        targeting_error = tools -> targeting_error(distance, targeting_angular_error);
        total_scattering = tools -> total_scattering(beam_widening, targeting_error);
        dynamic_loss = tools -> dynamic_loss(total_scattering, mirror_diameter / 2);
        break;
    
    case SPACE_EARTH:
	static_loss = tools -> static_loss(molecular_scattering, molecular_absorption, aerosol_scattering, aerosol_absorption, layers, zenith);
	//coherence_length = tools -> beam_widening_space_to_ground(wave_length, distance_sections, distance, wind_speed, zenith, height_above_sea_level);
	beam_widening = tools -> beam_widening_atmosphere(distance, wave_length, coherence_length, aperture_diameter);
	targeting_error = tools -> targeting_error(distance, targeting_angular_error);
	total_scattering = tools -> total_scattering(beam_widening, targeting_error);
	dynamic_loss = tools -> dynamic_loss(total_scattering, mirror_diameter / 2);
        break;

    case SPACE_SPACE:
        static_loss = 1;
        beam_widening = tools -> beam_widening_vacuum(space_space_channel_length, wave_length, aperture_diameter);
        targeting_error = tools -> targeting_error(space_space_channel_length, targeting_angular_error);
        total_scattering = tools -> total_scattering(beam_widening, targeting_error);
        dynamic_loss = tools -> dynamic_loss(total_scattering, mirror_diameter / 2);
        break;
    }

    delete tools;
}

double BB84::get_qber(){
    return this -> qber;
}

BB84::BB84():QProtocol(){}
BB84::~BB84(){}
