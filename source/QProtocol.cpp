#include "../include/QProtocol.hpp"
#include "../include/values.hpp"
#include <iostream>
#include<fstream>

QProtocol::QProtocol(){
    init_loss();
    init_distance_sections();
}

/**
 * @brief Initialises the vectors of scattering and absorption with layers
 * 
 */
void QProtocol::init_loss(){
    std::vector<double> aerosol_absorption;
    std::vector<double> aerosol_scattering; 
    std::vector<double> molecular_absorption;
    std::vector<double> molecular_scattering;
    std::vector<double> layers;
}

/**
 * @brief Assigns a vlaue to the distance variable, based on the height and the zenith.
 * 
 */
void QProtocol::init_distance(){

    double a, b, c, d;

    double h = this->height_above_sea_level;
    double z = this->zenith;

    a = sqrt(pow(EARTH_RADIUS, 2) * pow(cos(RADIAN(z)), 2));
    b = 2 * EARTH_RADIUS * h;
    c = pow(h, 2);
    d = EARTH_RADIUS * cos(RADIAN(z));

    this->distance =  a + b + c - d;
} 

/**
 * @brief Divides the distance that the beam travels into sections.
 * 
 */
void QProtocol::init_distance_sections(){

    this -> distance_sections.push_back(0);

    for(int i = 0; i < 45; i++){
        if(distance_sections[i] < 1000){
            distance_sections.push_back(distance_sections[i] + 200);
            continue;
        }
        if(distance_sections[i] < 30000){
            distance_sections.push_back(distance_sections[i] + 1000);
            continue;
        }
        if(distance_sections[i] < 60000){
            distance_sections.push_back(distance_sections[i] + 5000);
            continue;
        }
        if(distance_sections[i] >= 60000){
            distance_sections.push_back(distance_sections[i] + 10000);
            continue;
        }
    }

    std::cout << "Sectioning distance..." << std::endl;
}

/**
 * @brief Returns the length of a given string.
 * 
 * @param string std::string - the string in question
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
 * @brief Splits a sting into substrings with a given separator
 * 
 * @param string std::string - the string that needs to be splitted
 * @param seperator char - a separator character, that parses the string
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

            std::vector<std::string> line_cells;
            line_cells = split(line, separator);

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

std::vector<double> QProtocol::get_molecular_scattering(){
    return this -> molecular_scattering;
}

QProtocol::~QProtocol(){}