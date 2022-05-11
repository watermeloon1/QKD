#ifndef QPROTOCOL_HPP
#define QPROTOCOL_HPP
#include <vector>
#include <string>

class QProtocol
{
protected:
	int direction; // SET the direction of the communication: 0 -> Earth-space; 1 -> space-Earth; 2 -> space-space

	double distance;			   // SET the distance that the beam has to travel
	double height_above_sea_level; // SET the height above sea level

	std::vector<double> distance_sectors; // the distance of the channel divided into sectors

	std::vector<double> molecular_scattering; // molecular scattering in different layers of the atmosphere
	std::vector<double> molecular_absorption; // molecular absorption in different layers of the atmosphere
	std::vector<double> aerosol_scattering;	  // aerosol scattering in different layers of the atmosphere
	std::vector<double> aerosol_absorption;	  // aerosol absorption in different layers of the atmosphere

	std::vector<double> layers; // the layers of the atmosphere in kilometers

	double zenith; // the zenith angle of the beam

	double wave_length;									  // SET
	double wind_speed;									  // SET
	double aperture_diameter;							  // SET
	double targeting_angular_error;						  // SET
	double mirror_diameter;								  // SET
	double space_space_channel_length;					  // SET
	double quantum_efficiency_of_detector;				  // SET
	double mean_photon_number_of_signal;				  // SET
	double probability_of_polarization_measurement_error; // SET
	double noise;										  // SET
	int number_of_detectors;							  // SET

	double static_loss;
	double coherence_length;
	double beam_widening;
	double targeting_error;
	double total_scattering;
	double dynamic_loss;
	double transmittance;

	double qber_value;

	std::string climate; // SET
	std::string season;	 // SET
	std::string weather; // SET

	void init_distance_sectors();
	void read_from_file();

	// double frequency_of_laser_firing;
	// double efficiency_of_quantum_operations_by_bob;
	// double transmittance_bob_to_alice;
	// double dynamic_loss_bob_to_alice;
	// double static_loss_bob_to_alice;

	virtual std::string get_protocol_name() = 0;
	virtual void qber();

public:
	QProtocol(double height_above_sea_level, double distance); // constructor
	~QProtocol();															  // destructor

	std::vector<double> get_molecular_scattering();
	std::vector<double> get_layers();
	double get_zenith();
	int get_direction();

	void set_direction(int direction);

	void set_wave_length(double wave_length);
	void set_wind_speed(double windspeed = 21);
	void set_aperture_diameter(double aperture_diameter);
	void set_targeting_angular_error(double targeting_angular_error);
	void set_mirror_diameter(double mirror_diameter);
	void set_space_space_channel_length(double space_space_channel_length);
	void set_quantum_efficiency_of_detector(double quantum_efficiency_of_detector);
	void set_mean_photon_number_of_signal(double mean_photon_number_of_signal);
	void set_probability_of_polarization_measurement_error(double probability_of_polarization_measurement_error);
	void set_noise(double noise);
	void set_number_of_detectors(double number_of_detectors);

	void set_scenario(std::string climate, std::string season, std::string weather);
	void set_climate(std::string climate);
	void set_season(std::string season);
	void set_weather(std::string weather);

	void cout_details();
};

#endif