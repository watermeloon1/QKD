#include <iostream>
#include "../include/QProtocol.hpp"
#include "../include/BB84.hpp"
#include "../include/Values.hpp"

int main()
{

	BB84 *q = new BB84(20000, 21000);

	delete q;

	return 0;
}
