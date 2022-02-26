#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>

double integral1(double a, double b, double interval, double& f1)
{
	//double f1{};
	double c = (static_cast<double>(b) - a) / interval;
	double counter = a;
	for (double i = 0; i < interval; i++)
	{

		f1 = f1 + (4 / (sqrt(4 - counter * counter))) * (counter + c - counter);
		counter = counter + c;
	}
	return f1;
}

double integral2(double a, double b, double interval, double& f2)
{
	//double f2{};
	double c = (static_cast<double>(b) - a) / interval;
	double counter = a;
	for (double i = 0; i < interval; i++)
	{

		f2 = f2 + (4 / (sqrt(4 - counter * counter))) * (counter - (counter - c));
		counter = counter + c;
	}
	return f2;
}

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

		double f1 = 0;
		double f2 = 0;

		double f1_1 = 0; double f1_2 = 0; double f1_3 = 0; double f1_4 = 0;
		std::thread thread1(integral1,a, 0.25, interval/4, std::ref(f1_1));
		std::thread thread2(integral1, 0.25, 0.5, interval/4, std::ref(f1_2));
		std::thread thread3(integral1, 0.5, 0.75, interval/4, std::ref(f1_3));
		std::thread thread4(integral1, 0.75, b, interval/4, std::ref(f1_4));


		//left
		auto start1 = std::chrono::high_resolution_clock::now();
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
		f1 = f1_1 + f1_2 + f1_3 + f1_4;
		auto finish1 = std::chrono::high_resolution_clock::now();
		auto vremya1 = std::chrono::duration_cast<std::chrono::microseconds>(finish1 - start1);

		double f2_1 = 0; double f2_2 = 0; double f2_3 = 0; double f2_4 = 0;
		std::thread thread5(integral1, a, 0.25, interval / 4, std::ref(f2_1));
		std::thread thread6(integral1, 0.25, 0.5, interval / 4, std::ref(f2_2));
		std::thread thread7(integral1, 0.5, 0.75, interval / 4, std::ref(f2_3));
		std::thread thread8(integral1, 0.75, b, interval / 4, std::ref(f2_4));

		//right
		auto start2 = std::chrono::high_resolution_clock::now();
		thread5.join();
		thread6.join();
		thread7.join();
		thread8.join();
		f2 = f2_1 + f2_2 + f2_3 + f2_4;
		auto finish2 = std::chrono::high_resolution_clock::now();
		auto vremya2 = std::chrono::duration_cast<std::chrono::microseconds>(finish2 - start2);
		std::cout << "intervalov: " << interval << std::endl
			<< "right - " << f1 << " time: " << vremya1.count() << " microseconds" << std::endl
			<< "left - " << f2 << " time: " << vremya2.count() << " microseconds" << std::endl;
	}
}
