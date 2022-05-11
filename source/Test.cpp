#include <iostream>
#include "../include/Tools.hpp"
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/Values.hpp"

#include <fstream>
#include <vector>

int main()
{

	BB84 *q = new BB84(20000, 21000);
	q->set_direction(EARTH_SPACE);
	q->set_wave_length(wave_length);
	q->set_wind_speed(wind_speed);
	q->set_aperture_diameter(aperture_diameter);
	q->set_targeting_angular_error(targeting_angular_error);
	q->set_mirror_diameter(mirror_diameter);
	q->set_space_space_channel_length(space_space_channel_length);
	q->set_quantum_efficiency_of_detector(quantum_efficiency_of_detector);
	q->set_mean_photon_number_of_signal(mean_photon_number_of_signal);
	q->set_probability_of_polarization_measurement_error(probability_of_polarization_measurement_error);
	q->set_noise(noise);
	q->set_number_of_detectors(number_of_detectors);

	q->qber();

	int dir = q->get_direction();
	std::cout << dir << std::endl;

	double qber_value = q->get_qber();
	std::cout << qber_value << std::endl;

	delete q;

	return 0;
}
