#include "../include/QProtocol.hpp"
#include "../include/Values.hpp"
#include "../include/Tools.hpp"
#include <iostream>
#include <fstream>

float round_decimal(double number, int decimal_place){
	return ceil(number * (pow(10, decimal_place))) / pow(10, decimal_place);
}

QProtocol::QProtocol(double height_above_sea_level, double distance)
{

	Tools tools;
	std::cout << "Calculating zenith angle..." << std::endl;
	this->zenith = tools.zenith(height_above_sea_level, distance);
	std::cout << "Zenith angle is: " << this->zenith << "°" << std::endl << std::endl;

	std::cout << "Calculating distance..." << std::endl;
	this->distance = distance;
	std::cout << "Distance is: " << this->distance << " km" << std::endl << std::endl;

	std::cout << "Calculating height above sea level..." << std::endl;
	this->height_above_sea_level = height_above_sea_level;
	std::cout << "Height above sea level is: " << this->height_above_sea_level << " km" << std::endl << std::endl;

	std::cout << "Initialising conditions..." << std::endl;
	set_conditions("Midlatitude","Summer", "Clear");
	std::cout << "Climate: " << this->climate << std::endl;
	std::cout << "Season: " << this->season << std::endl;
	std::cout << "Weather: " << this->weather << std::endl << std::endl;
	
	std::cout << "Initialising sectors..." << std::endl;
	init_distance_sectors();
	for(int i = 1; i < this->distance_sectors.size(); ++i){
		std::cout << i << ".";
		if(i < 10){std::cout << " ";}
		std::cout << " sector: " << this->distance_sectors[i-1] << " - " << this->distance_sectors[i] << " km"<< std::endl;
	}
	std::cout << std::endl;

	std::cout << "Reading from file..." << std::endl << std::endl;
	read_from_file();
	
	std::cout << "\tMOLECULAR\tMOLECULAR\tAEROSOL\t\tAEROSOL" << std::endl;
	std::cout << "LAYERS\tSCATTERING\tABSORPTION\tSCATTERING\tABSORPTION" << std::endl << std::endl;

	for(int i = 1; i < this->layers.size(); ++i){
		std::cout << this->layers[i] << "\t" << round_decimal(molecular_scattering[i], 5) << "\t\t" << round_decimal(this->molecular_absorption[i], 5) << "\t\t" << round_decimal(this->aerosol_scattering[i], 5) << "\t\t" << round_decimal(this->aerosol_absorption[i], 5) << std::endl;
	}

	set_direction(EARTH_SPACE);
	set_wave_length(WAVELENGTH);
	set_wind_speed(WINDSPEED);
	set_aperture_diameter(APERTURE_DIAM);
	set_targeting_angular_error(TARGETING_ANGULAR_ERROR);
	set_mirror_diameter(MIRROR_DIAM);
	set_space_space_channel_length(SPACE_SPACE_CHAN_LENGTH);
	set_quantum_efficiency_of_detector(DETECTOR_QEFF);
	set_mean_photon_number_of_signal(SIGNAL_MEANPHN);
	set_probability_of_polarization_measurement_error(PROB_PME);
	set_noise(NOISE);
	set_number_of_detectors(DETECTOR_NUM);
	
	std::cout << std::endl << "DEFAULT VALUES " << std::endl;
	std::cout << "--------------" << std::endl;
	std::cout << "Wavelength: " << WAVELENGTH << std::endl;
	std::cout << "Windspeed: " << WINDSPEED << std::endl;
	std::cout << "Aperture diameter: " << APERTURE_DIAM << std::endl;
	std::cout << "Targeting angular error: "  << TARGETING_ANGULAR_ERROR << std::endl;
	std::cout << "Mirror diameter: " << MIRROR_DIAM << std::endl;
	std::cout << "Space-space channel length: " << SPACE_SPACE_CHAN_LENGTH << std::endl;
	std::cout << "Quantum efficiency of detector: " << DETECTOR_QEFF << std::endl;
	std::cout << "Mean phon number of signal: " << SIGNAL_MEANPHN << std::endl;
	std::cout << "Probbability of polarisation measurement error: " << PROB_PME << std::endl;
	std::cout << "Total noise: "  << NOISE << std::endl;
	std::cout << "Number of detectors: " << DETECTOR_NUM << std::endl;
	
}

void QProtocol::qber() {std::cout << "QBER values were not generated" << std::endl;}

/**
 * @brief Initialises the distance and the sectors of the distance.
 *
 * @param height_above_sea_level - the position of the sattelite
 */
void QProtocol::init_distance_sectors()
{

	// double a, b, c, d;

	// a = pow(EARTH_RADIUS, 2) * pow(cos(RADIAN(zenith)), 2);
	// b = 2 * EARTH_RADIUS * height_above_sea_level;
	// c = pow(height_above_sea_level, 2);
	// d = EARTH_RADIUS * cos(RADIAN(zenith));
	// this -> distance =  sqrt(a + b + c) - d;

	double distance_temp = this->distance;

	distance_sectors.push_back(0);

	for (int i = 0; distance_temp > 0; i++)
	{
		if (distance_sectors[i] < 1000)
		{
			distance_sectors.push_back(distance_sectors[i] + 200);
			distance_temp -= 200;
			continue;
		}
		if (distance_sectors[i] < 30000)
		{
			distance_sectors.push_back(distance_sectors[i] + 1000);
			distance_temp -= 1000;
			continue;
		}
		if (distance_sectors[i] < 60000)
		{
			distance_sectors.push_back(distance_sectors[i] + 5000);
			distance_temp -= 5000;
			continue;
		}
		if (distance_sectors[i] >= 60000)
		{
			distance_sectors.push_back(distance_sectors[i] + 10000);
			distance_temp -= 10000;
			continue;
		}
	}

	distance_sectors[distance_sectors.size() - 1] += distance_temp;
}

/**
 * @brief Returns the length of a given string.
 *
 * @param string - the string in question
 * @return int - the length of the string
 */
int length(std::string string)
{
	int length = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}

/**
 * @brief Splits a sting into substrings with a given separator.
 *
 * @param string - the string that needs to be splitted
 * @param separator - a separator character, that parses the string
 * @return std::vector<std::string> - the vector of substrings
 */
std::vector<std::string> split(std::string string, char separator)
{
	int i = 0;
	int startIndex = 0, endIndex;
	std::vector<std::string> strings;

	while (i <= length(string))
	{
		if (string[i] == separator || i == length(string))
		{
			endIndex = i;
			std::string substring = "";

			substring.append(string, startIndex, endIndex - startIndex);
			strings.push_back(substring);
			startIndex = endIndex + 1;
		}
		i++;
	}
	return strings;
}

/**
 * @brief Reads from the given resource file, that contains the values for the different scenarios.
 *
 */
void QProtocol::read_from_file()
{
	std::ifstream fin;
	std::string line;
	int line_position = 0;

	char separator = ';';

	// Open an existing file
	fin.open("resource/layer_data.csv");

	while (!fin.eof())
	{

		fin >> line;
		if (line_position > 6)
		{

			std::vector<std::string> line_cells = split(line, separator);

			this->layers.push_back(atof(line_cells[0].c_str()));

			if (this->climate.compare("Tropical") == 0)
			{
				this->molecular_absorption.push_back(atof(line_cells[2].c_str()));
				this->molecular_scattering.push_back(atof(line_cells[3].c_str()));
                std::cout << molecular_scattering.size() << std::endl;
			}
			else if (this->climate.compare("Midlatitude") == 0)
			{
				if (this->season.compare("Summer") == 0)
				{
					this->molecular_absorption.push_back(atof(line_cells[5].c_str()));
					this->molecular_scattering.push_back(atof(line_cells[6].c_str()));
				}
				else if (this->season.compare("Winter") == 0)
				{
					this->molecular_absorption.push_back(atof(line_cells[8].c_str()));
					this->molecular_scattering.push_back(atof(line_cells[9].c_str()));
				}
			}

			if (this->weather.compare("Clear") == 0)
			{
				this->aerosol_absorption.push_back(atof(line_cells[11].c_str()));
				this->aerosol_scattering.push_back(atof(line_cells[12].c_str()));
			}
			else if (this->weather.compare("Hazy") == 0)
			{
				this->aerosol_absorption.push_back(atof(line_cells[14].c_str()));
				this->aerosol_scattering.push_back(atof(line_cells[15].c_str()));
			}
		}
		line_position += 1;
	}

	fin.close();
}

//-------------GETTERS-------------//

std::vector<double> QProtocol::get_molecular_scattering()
{
	return this->molecular_scattering;
}

std::vector<double> QProtocol::get_layers()
{
	return this->layers;
}

double QProtocol::get_zenith()
{
	return this->zenith;
}

int QProtocol::get_direction()
{
	return this->direction;
}

//-------------SETTERS-------------//

void QProtocol::set_direction(int direction)
{
	this->direction = direction;
}

void QProtocol::set_conditions(std::string climate, std::string season, std::string weather)
{
	this->climate = climate;
	this->season = season;
	this->weather = weather;
}

void QProtocol::set_climate(std::string climate)
{
	this->climate = climate;
}

void QProtocol::set_season(std::string season)
{
	this->season = season;
}

void QProtocol::set_weather(std::string weather)
{
	this->weather = weather;
}

void QProtocol::set_wave_length(double wave_length)
{
	this->wave_length = wave_length;
}

void QProtocol::set_wind_speed(double wind_speed)
{
	this->wind_speed = wind_speed;
}

void QProtocol::set_aperture_diameter(double aperture_diameter)
{
	this->aperture_diameter = aperture_diameter;
}

void QProtocol::set_targeting_angular_error(double targeting_angular_error)
{
	this->targeting_angular_error = targeting_angular_error;
}

void QProtocol::set_mirror_diameter(double mirror_diameter)
{
	this->mirror_diameter = mirror_diameter;
}

void QProtocol::set_space_space_channel_length(double space_space_channel_length)
{
	this->space_space_channel_length = space_space_channel_length;
}

void QProtocol::set_quantum_efficiency_of_detector(double quantum_efficiency_of_detector)
{
	this->quantum_efficiency_of_detector = quantum_efficiency_of_detector;
}
void QProtocol::set_mean_photon_number_of_signal(double mean_photon_number_of_signal)
{
	this->mean_photon_number_of_signal = mean_photon_number_of_signal;
}

void QProtocol::set_probability_of_polarization_measurement_error(double probability_of_polarization_measurement_error)
{
	this->probability_of_polarization_measurement_error = probability_of_polarization_measurement_error;
}

void QProtocol::set_noise(double noise)
{
	this->noise = noise;
}

void QProtocol::set_number_of_detectors(double number_of_detectors)
{
	this->number_of_detectors = number_of_detectors;
}

//-------------COUT-------------//

void QProtocol::print_figures()
{

	

}

QProtocol::~QProtocol() {}