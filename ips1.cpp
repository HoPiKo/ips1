#include <math.h>
#include <iostream>
#include <chrono>

int main()
{
	//function: 4/(sqrt(4 - x^2)) interval: 0 - 1

	int a = 0;
	int b = 1;
	int interval;
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0: interval = 100;
			break;
		case 1: interval = 1000;
			break;
		case 2: interval = 10000;
			break;
		case 3: interval = 100000;
			break;
		case 4: interval = 1000000;
			break;
		default:
			break;
		}

		double c;
		c = (static_cast<double>(b) - a) / interval;
		double f1 = 0;
		double f2 = 0;
		double counter = 0;
		//left
		auto start1 = std::chrono::high_resolution_clock::now();
		for (double i = 0; i < interval; i++)
		{

			f1 = f1 + (4 / (sqrt(4 - counter * counter))) * (counter + c - counter);
			counter = counter + c;
		}
		auto finish1 = std::chrono::high_resolution_clock::now();
		auto vremya1 = std::chrono::duration_cast<std::chrono::microseconds>(finish1 - start1);

		//right
		auto start2 = std::chrono::high_resolution_clock::now();
		counter = 0;
		for (double i = 0; i < interval; i++)
		{
			counter = counter + c;
			f2 = f2 + (4 / (sqrt(4 - counter * counter))) * (counter - (counter - c));

		}
		auto finish2 = std::chrono::high_resolution_clock::now();
		auto vremya2 = std::chrono::duration_cast<std::chrono::microseconds>(finish2 - start2);
		std::cout << "intervalov: " << interval << std::endl
			<< "right - " << f1 << " time: " << vremya1.count() << " microseconds" << std::endl
			<< "left - " << f2 << " time: " << vremya2.count() << " microseconds" << std::endl;
	}
}
