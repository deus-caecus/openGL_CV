#include "pixelTool.h"
#include"function.h"
#include<iostream>

 

int main()
{
	std::cout << "run on openGL" << std::endl;
	std::cout << "select the following number to show the algorithm: " << std::endl;
	std::cout << "1.DDALine 2.scanlineAreaFill 3.sutherland-Hodgman" << std::endl;
	bool loop = true;
	int choice;
	while (loop)
	{
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			DDALineMain();
			break;
		case 2:
			ScanLineFillMain();
			break;
		case 3:
			sutherlandHodgmanMain();
			break;
		default:
			loop  = false;
		}
	}
	return 0;
}


