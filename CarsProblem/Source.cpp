#include "bridge.h"
#include "TrafficSwitcher.h"
#include "CarFactory.h"

int main()
{
	CarFactory cf;
	// produce two car from left side 2 from right
	cf.produceCar(4);

	system("pause");

	return 0;
}