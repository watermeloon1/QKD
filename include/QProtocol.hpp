#ifndef QPROTOCOL_HPP
#define QPROTOCOL_HPP
#include <vector>
#include <string>

class QProtocol{
	protected:
        int direction; // the direction of the communication: 0 -> Earth-space; 1 -> space-Earth; 2 -> space-space
		double distance; // the distance that the beam has to travel
		std::vector <double> distance_sectors; // the distance of the channel divided into sectors
        
        std::vector<double> molecular_scattering; // molecular scattering in different layers of the atmosphere
        std::vector<double> molecular_absorption; // molecular absorption in different layers of the atmosphere
        std::vector<double> aerosol_scattering; // aerosol scattering in different layers of the atmosphere
        std::vector<double> aerosol_absorption; // aerosol absorption in different layers of the atmosphere

        std::vector<double> layers; // the layers of the atmosphere in kilometers

        double zenith; // the zenith angle of the beam
        double wave_length;
        double wind_speed;
	    double height_above_sea_level; // height above sea level in kilometers
	    double aperture_diameter;
	    double targeting_angular_error;
	    double mirror_diameter;
	    double space_space_channel_length;
	    double quantum_efficiency_of_detector;
	    double mean_photon_number_of_signal;
	    double qber_value;
	    double probability_of_polarization_measurement_error;
	    double noise;
	    int number_of_detectors;
	    double static_loss;
	    double coherence_length;
	    double beam_widening;
		double targeting_error;
    	double total_scattering;
	    double dynamic_loss;
	    double transmittance;
	    
	    std::string weather;
	    std::string climate;
	    std::string season;

		void init_distance(double height_above_sea_level, double zenith); 
		void init_loss();
		void read_from_file();

		//double frequency_of_laser_firing;
	    //double efficiency_of_quantum_operations_by_bob;
	    //double transmittance_bob_to_alice;
	    //double dynamic_loss_bob_to_alice;
	    //double static_loss_bob_to_alice;

		virtual std::string get_protocol_name() = 0;
		virtual void qber() = 0;

	public: 

		QProtocol(double height_above_sea_level, double zenith); // constructor
		~QProtocol(); // destructor

		std::vector<double> get_molecular_scattering();
		double get_zenith();

		void set_direction(int direction);
		void set_weather(std::string weather);
		void set_climate(std::string climate);
		void set_season(std::string season);

		void cout_distance_sectors();
};

#endif