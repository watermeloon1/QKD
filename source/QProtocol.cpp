#include "../include/QProtocol.hpp"
#include "../include/Values.hpp"
#include "../include/Tools.hpp"
#include <iostream>
#include <fstream>

QProtocol::QProtocol(double height_above_sea_level, double distance)
{

	Tools *tools = new Tools();

	this->zenith = tools->zenith(height_above_sea_level, distance);
	this->distance = distance;
	this->height_above_sea_level = height_above_sea_level;

	init_distance_sectors(height_above_sea_level);
	read_from_file();

	delete tools;
}

/**
 * @brief Initialises the distance and the sectors of the distance.
 *
 * @param height_above_sea_level - the position of the sattelite
 */
void QProtocol::init_distance_sectors(double height_above_sea_level)
{

	// double a, b, c, d;

	// a = pow(EARTH_RADIUS, 2) * pow(cos(RADIAN(zenith)), 2);
	// b = 2 * EARTH_RADIUS * height_above_sea_level;
	// c = pow(height_above_sea_level, 2);
	// d = EARTH_RADIUS * cos(RADIAN(zenith));

	// this -> distance =  sqrt(a + b + c) - d;

	std::cout << "Total distance: " << this->distance << std::endl;
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

	// std::cout << "distance_temp: " << distance_temp << std::endl;
	std::cout << "Number of sectors:" << distance_sectors.size() << std::endl;
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
	int startIndex = 0, endIndex = 0;
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

	std::cout << "Reading from file..." << std::endl;

	std::ifstream fin;
	std::string line;
	int line_position = 0;

	std::vector<std::string> line_cells;
	char separator = ';';

	// Open an existing file
	fin.open("resource/asv_860.csv");

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
	std::cout << "qber_value" << std::endl;
	return this->direction;
}

//-------------SETTERS-------------//

void QProtocol::set_direction(int direction)
{
	this->direction = direction;
	std::cout << "set_direction" << std::endl;
	std::cout << "direction: " << direction << std::endl;
	std::cout << "this.direction: " << this -> direction << std::endl;
}

void QProtocol::set_scenario(std::string climate, std::string season, std::string weather)
{
	this->climate = climate;
	this->climate = climate;
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

void QProtocol::set_wind_speed(double windspeed)
{
	this->wind_speed = windspeed;
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

void QProtocol::cout_details()
{
}

QProtocol::~QProtocol() {}