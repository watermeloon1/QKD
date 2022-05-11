#include <math.h>

#define PI 3.14159265
#define EARTH_RADIUS 6378
#define EARTH_SPACE 0
#define SPACE_EARTH 1
#define SPACE_SPACE 2
#define A (1.7 * pow(10, -14))
#define DEGREE(radian) radian * 180 / PI
#define RADIAN(degree) degree *PI / 180
#define METER(kilometer) kilometer * 1000
#define WAVE(length) 2 * PI / (length * pow(10, -9))

static double wave_length = 860; // nm
static double wave_length_MIN = 800; // nm
static double wave_length_MAX = 1200; // nm

static double wind_speed = 21; // m/s
static double wind_speed_MIN = 15; // m/s
static double wind_speed_MAX = 25; // m/s

static double aperture_diameter = 0.2; // m
static double aperture_diameter_MIN = 0.1; // m
static double aperture_diameter_MAX = 0.5; // m


static double targeting_angular_error = 0.5; // μrad
static double targeting_angular_error_MIN = 0.3; // μrad
static double targeting_angular_error_MAX = 0.7; // μrad

static double mirror_diameter = 2; // m
static double mirror_diameter_MIN = 1; // m
static double mirror_diameter_MAX = 4; // m

static double space_space_channel_length = 1000; // km

static double quantum_efficiency_of_detector = 0.7; 
static double quantum_efficiency_of_detector_MIN = 0.5; 
static double quantum_efficiency_of_detector_MAX = 0.9; 

static double mean_photon_number_of_signal = 0.1; 
static double mean_photon_number_of_signal_MIN = 0.05; 
static double mean_photon_number_of_signal_MAX = 0.15; 

static double probability_of_polarization_measurement_error = 0.0001; 
static double probability_of_polarization_measurement_error_MIN = 0.0001; 
static double probability_of_polarization_measurement_error_MAX = 0.0005; 

static double noise = 0.0000002; 
static double noise_MIN = 0.0000002; 
static double noise_MAX = 0.0000005;

static double number_of_detectors = 4;
static double number_of_detectors_MIN = 1;
static double number_of_detectors_MAX = 5;
