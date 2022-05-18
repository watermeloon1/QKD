#include <iostream>
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/Values.hpp"

int main(void)
{

	BB84 *q = new BB84(789, 925);
	delete q;

	return 0;
}
