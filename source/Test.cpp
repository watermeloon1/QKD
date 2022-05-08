#include <iostream>
#include "../include/Tools.hpp"
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/Values.hpp"

#include<fstream>
#include <vector>

int main(){

    BB84 *q = new BB84(20000, 21000, 0);
    //q->set_wave_length();
    //q->set_windspeed();
    //q->set_aperture_diameter();
    //q->set_targeting_angular_error();
    //q->set_mirror_diameter();
    //q->set_space_space_channel_length();
    //q->set_quantum_efficiency_of_detector();
    //q->set_mean_photon_number_of_signal();
    //q->set_probability_of_polarization_measurement_error();
    //q->set_noise();
    //q->set_number_of_detectors();

    q->qber();

    delete q;

    return 0;
}
