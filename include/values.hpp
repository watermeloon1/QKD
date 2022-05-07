#include <math.h>

#define PI 3.14159265 
#define EARTH_RADIUS 6378
#define EARTH_SPACE 0
#define SPACE_EARTH 1
#define SPACE_SPACE 2

/**
 * @brief Converts radians to degrees.
 * 
 */
#define DEGREE(radian) radian * 180 / PI
/**
 * @brief Converts degrees to radians.
 * 
 */
#define RADIAN(degree) degree * PI / 180
/**
 * @brief Converts kilometers to meters.
 * 
 */
#define METER(kilometer) kilometer * 1000
/**
 * @brief Converts wavelength to a wavenumber, that can be used in calculations.
 * 
 */
#define WAVE(length) 2 * PI / (length * pow(10, -9))

