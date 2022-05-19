#ifndef BB84_HPP
#define BB84_HPP
#include "QProtocol.hpp"

class BB84 : public QProtocol
{
public:
	BB84(double height_above_sea_level, double distance); // constructor
	~BB84();															 // destructor

	std::string get_protocol_name() override;
	void qber() override;
};

#endif