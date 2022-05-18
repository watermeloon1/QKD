#include <math.h>

#define PI 3.14159265
#define EARTH_RADIUS 6378
#define EARTH_SPACE 0
#define SPACE_EARTH 1
#define SPACE_SPACE 2
#define A (1.7 * pow(10, -14))
#define TO_DEGREE(radian) radian * 180 / PI
#define TO_RADIAN(degree) degree * PI / 180
#define TO_METER(kilometer) kilometer * 1000
#define TO_WAVE(length) 2 * PI / (length * pow(10, -9))

#define WAVELENGTH 860 // nm
#define WAVELENGTH_MIN 800 // nm
#define WAVELENGTH_MAX 1200 // nm

#define WINDSPEED 21 // m/s
#define WINDSPEED_MIN 15 // m/s
#define WINDSPEED_MAX 25 // m/s

#define APERTURE_DIAM 0.2 // m
#define APERTURE_DIAM_MIN 0.1 // m
#define APERTURE_DIAM_MAX 0.5 // m


#define TARGETING_ANGULAR_ERROR 0.5 // μrad
#define TARGETING_ANGULAR_ERROR_MIN 0.3 // μrad
#define TARGETING_ANGULAR_ERROR_MAX 0.7 // μrad

#define MIRROR_DIAM 2 // m
#define MIRROR_DIAM_MIN 1 // m
#define MIRROR_DIAM_MAX 4 // m

#define SPACE_SPACE_CHAN_LENGTH 1000 // km

#define DETECTOR_QEFF 0.7 
#define DETECTOR_QEFF_MIN 0.5 
#define DETECTOR_QEFF_MAX 0.9 

#define SIGNAL_MEANPHN 0.1 
#define SIGNAL_MEANPHN_MIN 0.05 
#define SIGNAL_MEANPHN_MAX 0.15 

#define PROB_PME 0.0001 
#define PROB_PME_MIN 0.0001 
#define PROB_PME_MAX 0.0005 

#define NOISE 0.0000002 
#define NOISE_MIN 0.0000002 
#define NOISE_MAX 0.0000005

#define DETECTOR_NUM 4
#define DETECTOR_NUM_MIN 1
#define DETECTOR_NUM_MAX 5
