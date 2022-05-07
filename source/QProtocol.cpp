#include "../include/QProtocol.hpp"
#include "../include/Values.hpp"
#include <iostream>
#include <fstream>

QProtocol::QProtocol(double height_above_sea_level, double zenith){
    init_distance(height_above_sea_level, zenith);
    read_from_file();
}

/**
 * @brief Initialises the distance and the sectors of the distance.
 *  
 * @param height_above_sea_level - the position of the sattelite
 * @param zenith - the zenith angle of the beam hitting Earth ( °)
 */
void QProtocol::init_distance(double height_above_sea_level, double zenith){

    double a, b, c, d;

    this -> height_above_sea_level = height_above_sea_level;
    this -> zenith = zenith;

    a = pow(EARTH_RADIUS, 2) * pow(cos(RADIAN(zenith)), 2);
    b = 2 * EARTH_RADIUS * height_above_sea_level;
    c = pow(height_above_sea_level, 2);
    d = EARTH_RADIUS * cos(RADIAN(zenith));

    this -> distance =  sqrt(a + b + c) - d;

    std::cout << "Total distance: " << this -> distance << std::endl;

    double distance_temp = this -> distance;

    this -> distance_sectors.push_back(0);

    for(int i = 0; distance_temp > 0; i++){
        if(distance_sectors[i] < 1000){
            distance_sectors.push_back(distance_sectors[i] + 200);
            distance_temp -= 200;
            continue;
        }
        if(distance_sectors[i] < 30000){
            distance_sectors.push_back(distance_sectors[i] + 1000);
            distance_temp -= 1000;
            continue;
        }
        if(distance_sectors[i] < 60000){
            distance_sectors.push_back(distance_sectors[i] + 5000);
            distance_temp -= 5000;
            continue;
        }
        if(distance_sectors[i] >= 60000){
            distance_sectors.push_back(distance_sectors[i] + 10000);
            distance_temp -= 10000;
            continue;
        }    
    }
    distance_sectors[distance_sectors.size()-1] += distance_temp;

    //std::cout << "distance_temp: " << distance_temp << std::endl;
    std::cout << "Number of sectors:" << distance_sectors.size() << std::endl;
}

/**
 * @brief Returns the length of a given string.
 * 
 * @param string - the string in question
 * @return int - the length of the string
 */
int length(std::string string){ 
    int length = 0;  
    for (int i = 0; string[i] != '\0'; i++){  
        length++;  
    }  
    return length;     
} 

/**
 * @brief Splits a sting into substrings with a given separator.
 * 
 * @param string - the string that needs to be splitted
 * @param seperator - a separator character, that parses the string
 * @return std::vector<std::string> - the vector of substrings
 */
std::vector<std::string> split(std::string string, char separator){  
    int i = 0;  
    int startIndex = 0, endIndex = 0;  
    std::vector<std::string> strings;

    while (i <= length(string)){  
        if (string[i] == separator || i == length(string)){  
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
 * @brief Reads from the given resource file, that containis the values for the different scenarios.
 * 
 */
void QProtocol::read_from_file(){

    std::cout << "Reading from file..." << std::endl;
    
    std::ifstream fin;
    std::string line;
    int line_position = 0;

    std::vector<std::string> line_cells;
    char separator = ';';

    // Open an existing file
    fin.open("../resources/asv_860.csv");
    
    while(!fin.eof()){

        fin >> line;
        if(line_position > 6){

            std::vector<std::string> line_cells = split(line, separator);

            this -> layers.push_back(atof(line_cells[0].c_str()));

            if(this -> climate.compare("Tropical") == 0){
                this -> molecular_absorption.push_back(atof(line_cells[2].c_str()));
                this -> molecular_scattering.push_back(atof(line_cells[3].c_str()));

            }else if(this -> climate.compare("Midlatitude") == 0){
                if(this -> season.compare("Summer") == 0){
                    this -> molecular_absorption.push_back(atof(line_cells[5].c_str()));
                    this -> molecular_scattering.push_back(atof(line_cells[6].c_str()));
                }else if(this -> season.compare("Winter") == 0){
                    this -> molecular_absorption.push_back(atof(line_cells[8].c_str()));
                    this -> molecular_scattering.push_back(atof(line_cells[9].c_str()));
                }
            }

            if(this -> weather.compare("Clear") == 0){
                this -> aerosol_absorption.push_back(atof(line_cells[11].c_str()));
                this -> aerosol_scattering.push_back(atof(line_cells[12].c_str()));
            }else if(this -> weather.compare("Hazy") == 0){
                this -> aerosol_absorption.push_back(atof(line_cells[14].c_str()));
                this -> aerosol_scattering.push_back(atof(line_cells[15].c_str()));
            }

        }
        line_position += 1;
    }

    fin.close();
}

std::vector<double> QProtocol::get_molecular_scattering(){
    return this -> molecular_scattering;
}

double QProtocol::get_zenith(){
    return this -> zenith;
}

void QProtocol::set_direction(int direction){
    this -> direction = direction;
}

void QProtocol::set_weather(std::string weather){
    this -> weather = weather;
}

void QProtocol::set_climate(std::string climate){
    this -> climate = climate;
}

void QProtocol::set_season(std::string season){
    this -> season = season;
}

void QProtocol::cout_distance_sectors(){
    for(int i = 0; i < distance_sectors.size(); i++){
        std::cout << distance_sectors[i] << std::endl;
    }
}

QProtocol::~QProtocol(){}