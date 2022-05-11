#include <vector>
#include "../include/Tools.hpp"
#include "../include/Values.hpp"

/**
 * @brief Calculates the zenit angle of the beam hitting/leaving the surface of Earth.
 *
 * @param distance_to_earth - the shortest distance between the satellite and the surface of Earth (km)
 * @param distance_to_base - the shortest distance between the satellite and the communicating base (km)
 * @return double - the zenith angle of the beam hitting Earth ( °)
 */
double Tools::zenith(double distance_to_earth, double distance_to_base)
{

	if (distance_to_earth <= distance_to_base)
	{

		double numerator, denominator, alfa_radian, alfa_degree, zenith_degree;

		numerator = pow(EARTH_RADIUS, 2) + pow(distance_to_base, 2) - pow(EARTH_RADIUS + distance_to_earth, 2);
		denominator = 2 * EARTH_RADIUS * distance_to_base;
		alfa_radian = acos(numerator / denominator);
		alfa_degree = DEGREE(alfa_radian);
		zenith_degree = 180 - alfa_degree;

		return zenith_degree;
	}
	else
	{
		return -1;
	}
}

/**
 * @brief The beam widening of a beam going through vacuum.
 *
 * @param distance - the distance between the emitter and the receiver (km)
 * @param telescope_aperture - the aperture of the emitting telescope (m)
 * @param wavelenght - the wavelength of the beam (nm)
 * @return double - the extent of the widening (m)
 */
double Tools::beam_widening_vacuum(double distance, double telescope_aperture, double wavelenght)
{

	double a, b, c;

	double wavenumber = WAVE(wavelenght);
	double distance_m = METER(distance);

	a = 4 * pow(distance_m, 2);
	b = pow(wavenumber, 2) * pow(telescope_aperture, 2);
	c = pow(telescope_aperture, 2);

	return sqrt(a / b + c / 4);
}

/**
 * @brief The beam widening of a beam going through the atmosphere.
 *
 * @param distance - the distance between the emitter and the receiver (km)
 * @param telescope_aperture - the aperture of the emitting telescope (m)
 * @param wavelenght - the wavelength of the beam (nm)
 * @param coherence_length - length of the coherence
 * @return double - the extent of the widening (m)
 */
double Tools::beam_widening_atmosphere(double distance, double telescope_aperture, double wavelenght, double coherence_length)
{

	double a, b, c, d, e, f;

	double wavenumber = WAVE(wavelenght);
	double distance_m = METER(distance);

	a = 4 * pow(distance_m, 2);
	b = pow(wavenumber, 2) * pow(telescope_aperture, 2);
	c = pow(telescope_aperture, 2);
	d = 4 * pow(distance_m, 2);
	e = pow(wavenumber * coherence_length, 2);
	f = pow(1 - 0.62 * (pow(coherence_length / telescope_aperture, 1 / 3)), 6 / 5);

	return sqrt(a / b + c / 4 + d / e * f);
}

/**
 * @brief The strength of the turbulence in the atmosphere of Earth.
 *
 * @param height_above_sea_level - the height of the observed position (km)
 * @param wind_speed - the speed of the wind at the given height (m/s)
 * @return double - the strength of the turbulence
 */
double Tools::turbulence_strength(double height_above_sea_level, double wind_speed)
{

	double a, b, c, d, e;

	a = 0.00594 * pow((wind_speed / 27), 2);
	b = pow(height_above_sea_level * pow(10, -5), 10);
	c = exp(height_above_sea_level / -1000);
	d = 2.7 * pow(10, -6) * exp(height_above_sea_level / -1500);
	e = A * exp(height_above_sea_level / -100);

	return a * b * c + d + e;
}

/**
 * @brief Calculates the targeting error of the beam.
 *
 * @param distance - the distance between the emitter and the receiver (km)
 * @param angular_error - the deviation from the optimal direction (μrad)
 * @return double - the deviation from the target (m)
 */
double Tools::targeting_error(double distance, double angular_error)
{

	double a, b;

	double distance_m = METER(distance);

	a = distance_m * angular_error;
	b = pow(10, -6);

	return a * b;
}

/**
 * @brief The total scattering of the beam.
 *
 * @param beam_radius - the radius of the beam
 * @param targeting_error - the targeting error of the beam (m)
 * @return double - the total scattering of the beam (m)
 */
double Tools::total_scattering(double beam_radius, double targeting_error)
{

	double a, b;

	a = sqrt(pow(beam_radius, 2));
	b = pow(targeting_error, 2);

	return a + b;
}

/**
 * @brief Calculates the dynamic loss of the channel.
 *
 * @param total_scattering - the total scattering of the beam (m)
 * @param mirror_radius - the mirror radius of the receiver (m)
 * @return - the total dynamic loss of the channel
 */
double Tools::dynamic_loss(double total_scattering, double mirror_radius)
{

	double a, b;

	a = (-1) * pow(mirror_radius, 2);
	b = 2 * pow(total_scattering, 2);

	return 1 - exp(a / b);
}

/**
 * @brief Calculates the static loss of the beam going through the atmosphere of Earth.
 *
 * @param molecular_scattering  - the molecular scattering of the beam due to climate conditions
 * @param molecular_absorption  - the molecular absorption of the atmosphere
 * @param aerosol_scattering - the molecular scattering of the beam due to weather conditions
 * @param aerosol_absorption - the aerosol absorption of the atmosphere
 * @param layers_of_air - the atmosphere of Earth divided into layers on top of each other
 * @param zenith - the zenith angle of the beam hitting Earth ( °)
 * @return double - the sum of static loss in all of the layers
 * TODO: correction
 */
double Tools::static_loss(std::vector<double> molecular_scattering, std::vector<double> molecular_absorption,
						  std::vector<double> aerosol_scattering, std::vector<double> aerosol_absorption, std::vector<double> layers, double zenith)
{

	std::vector<double> scattering(molecular_scattering.size());

	for (int i = 0; i < molecular_scattering.size(); i++)
	{
		scattering[i] = molecular_scattering[i] + aerosol_scattering[i];
	}

	std::vector<double> absorption(molecular_absorption.size());

	for (int i = 0; i < molecular_absorption.size(); i++)
	{
		absorption[i] = molecular_absorption[i] + aerosol_absorption[i];
	}

	double sum_of_layers = 0;

	for (int i = 0; i < layers.size() - 1; i++)
	{
		sum_of_layers += (((scattering[i] + scattering[i + 1]) / 2) + ((absorption[i] + absorption[i + 1]) / 2)) *
											((layers[i + 1] - layers[i]) / cos(zenith * (PI / 180)));
	}

	return exp((-1) * sum_of_layers);
}

/**
 * @brief Calculates the total beam widening for the Earth-space direction.
 *
 * @param wavelength - the wavelength of the beam (nm)
 * @param sectors - the sectors of the distance that the beam travels
 * @param distance - the distance that the beam travels (km)
 * @param wind_speed - the speed of the wind
 * @param zenith - the zenith angle of the beam hitting Earth ( °)
 * @return double - the coherence length of the wave
 */
double Tools::beam_widening_earth_space(double wavelength, std::vector<double> sectors, double distance, double wind_speed, double zenith)
{

	double a, b, c, d, e;
	double t0, t1;

	double distance_m = METER(distance);
	double wavenumber = WAVE(wavelength);

	double sum = 0;

	for (int i = 0; i < sectors.size() - 1; i++)
	{

		t0 = turbulence_strength(sectors[i], wind_speed);
		t1 = turbulence_strength(sectors[i + 1], wind_speed);

		a = pow(1 - (sectors[i] / (distance_m * cos(RADIAN(zenith)))), 5 / 3);
		b = pow(1 - (sectors[i + 1] / (distance_m * cos(RADIAN(zenith)))), 5 / 3);
		c = (t0 * a + t1 * b) / 2;
		d = abs((sectors[i + 1] - sectors[i]) / cos(RADIAN(zenith)));
		e = c * d;

		sum += e;
	}

	sum = 1.46 * pow(wavenumber, 2) * sum;

	if (sum < 0)
	{

		sum *= (-1);
		sum = pow(sum, (-0.6));
		sum *= (-1);
		return sum;
	}
	else
	{
		return pow(sum, (-0.6));
	}
}

/**
 * @brief Calculates the total beam widening for the space-Earth direction.
 *
 * @param wavelength - the wavelength of the beam (nm)
 * @param sectors - the sectors of the distance that the beam travels
 * @param distance - the distance that the beam travels (km)
 * @param wind_speed - the speed of the wind
 * @param zenith - the zenith angle of the beam hitting Earth ( °)
 * @return double - the coherence length of the wave
 */
double Tools::beam_widening_space_earth(double wavelength, std::vector<double> sectors, double distance, double wind_speed, double zenith)
{

	double a, b, c, d, e;
	double t0, t1;

	double distance_m = METER(distance);
	double wavenumber = WAVE(wavelength);

	double sum = 0;

	for (int i = 0; i < sectors.size() - 1; i++)
	{

		t0 = turbulence_strength(sectors[i], wind_speed);
		t1 = turbulence_strength(sectors[i + 1], wind_speed);

		a = pow(1 - (distance_m - (sectors[i] / cos(RADIAN(zenith))) / distance_m), 5 / 3);
		b = pow(1 - (distance_m - (sectors[i + 1] / cos(RADIAN(zenith))) / distance_m), 5 / 3);
		c = (t0 * a + t1 * b) / 2;
		d = abs(sectors[i + 1] - sectors[i] / cos(RADIAN(zenith)));
		e = c * d;

		sum += e;
	}

	return pow(1.46 * pow(wavenumber, 2) * sum, -(0.6));
}
