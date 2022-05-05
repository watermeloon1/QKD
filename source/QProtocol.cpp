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
int length(std::string str){ 
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++){  
        length++;  
    }  
    return length;     
} 

std::vector<std::string> split(std::string str, char seperator){  
    int i = 0;  
    int startIndex = 0, endIndex = 0;  
    std::vector<std::string> strings;

    while (i <= length(str)){  
        if (str[i] == seperator || i == length(str)){  
            endIndex = i;  
            std::string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings.push_back(subStr);
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     

    return strings;
}  

void QProtocol::read_from_file(){

    std::cout << "Reading from file..." << std::endl;
    
    std::ifstream fin;
    std::string line;
    int line_position = 0;

    std::vector<std::string> line_cells;
    char separator = ';';

    // Open an existing file
    fin.open("../resources/asv_860.csv");
    std::cout << fin << std::endl;
    while(!fin.eof()){

        if(line_position > 6){
            fin >> line;
            line_cells.clear();

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
    for(int i = 0; i < this -> molecular_scattering.size(); i++){
        std::cout << this -> molecular_scattering[i] << std::endl;
    }
    return this -> molecular_scattering;
}

QProtocol::~QProtocol(){}