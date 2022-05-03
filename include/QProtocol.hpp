#ifndef QPROTOCOL_HPP
#define QPROTOCOL_HPP
#include <vector>
 
class QProtocol{
    protected:
        int direction; // the direction of the communication: 0 -> Earth-space; 1 -> space-Earth; 2 -> space-space
        double distance; // the distance that the beam has to travel
        std::vector <double> distance_sections;//

        double molecular_scattering[33];
        double molecular_absorption[33];
        double aerosol_scattering[33];
        double aerosol_absorption[33];

        double layers[33];

        double zenith;//
        double wave_length;
        double wind_speed;
	    double height_above_sea_level;//
	    double aperture_diameter;
	    double targeting_error;
	    double mirror_diameter;
	    double space_space_channel_length;
	    double frequency_of_laser_firing;
	    double quantum_efficiency_of_detector;
	    double mean_photon_number_of_signal;
	    double qber;
	    double probability_of_polarization_measurement_error;
	    double noise;
	    int number_of_detectors;
	    double efficiency_of_quantum_operations_by_bob;
	    double static_loss;
	    double coherence_length;
	    double beam_widening;
    	double total_scattering;
	    double dynamic_loss;
	    double transmittance;
	    double transmittance_bob_to_alice;
	    double dynamic_loss_bob_to_alice;
	    double static_loss_bob_to_alice;
	    std::string weather;
	    std::string climate;
	    std::string season;

	public: 

		QProtocol();
        virtual std::string get_protocol_name() = 0;
		void set_distance();
		void slice_distance();
		
};

#endif