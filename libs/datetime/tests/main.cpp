#include <exception>
#include <format>
#include <iostream>

#include "DateTime.hpp"

using namespace onion;

int main()
{

	std::cout << "------------- DATE TIME TESTS -------------\n" << std::endl;

	std::cout << "\nTesting default constructor (current UTC time):" << std::endl;
	DateTime dateTimeNow;
	std::cout << "Current UTC DateTime: " << dateTimeNow.toString() << std::endl;

	std::cout << "\nTesting UtcNow() static method:" << std::endl;
	DateTime utcNow = DateTime::UtcNow();
	std::cout << "UtcNow: " << utcNow.toString() << std::endl;

	std::cout << "\nTesting parameterized constructor with valid date and time:" << std::endl;
	DateTime specificDateTime(2024, 6, 15, 12, 30, 45, 500);
	std::cout << "Specific DateTime: " << specificDateTime.toString() << std::endl;

	std::cout << "\nTesting parameterized constructor with invalid date (February 30):" << std::endl;
	try
	{
		DateTime invalidDateTime(2024, 2, 30, 10, 0, 0);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Expected error for invalid date: " << ex.what() << std::endl;
	}

	std::cout << "\nTesting parameterized constructor with invalid time (25 hours):" << std::endl;
	try
	{
		DateTime invalidTimeDateTime(2024, 6, 15, 25, 0, 0);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Expected error for invalid time: " << ex.what() << std::endl;
	}

	std::cout << "\nTesting comparison operators:" << std::endl;
	DateTime dt1(2024, 6, 15, 12, 30, 45);
	DateTime dt2(2024, 6, 15, 12, 30, 45);
	DateTime dt3(2024, 6, 15, 13, 0, 0);

	std::cout << "dt1: " << dt1.toString() << std::endl;
	std::cout << "dt2: " << dt2.toString() << std::endl;
	std::cout << "dt3: " << dt3.toString() << std::endl;

	std::cout << "dt1 == dt2: " << (dt1 == dt2) << std::endl;
	std::cout << "dt1 != dt3: " << (dt1 != dt3) << std::endl;
	std::cout << "dt1 < dt3: " << (dt1 < dt3) << std::endl;
	std::cout << "dt3 > dt2: " << (dt3 > dt2) << std::endl;

	std::cout << "\nTesting toStringg() formating:" << std::endl;
	std::cout << "ISO 8601 format: " << dateTimeNow.toString() << std::endl;
	std::cout << "Custom format (\"%Y-%m-%d %H:%M:%S\"): " << dateTimeNow.toString("%Y-%m-%d %H:%M:%S") << std::endl;

	std::cout << "\nTesting toUnixTimestamp():" << std::endl;
	std::cout << "Current UTC DateTime: " << dateTimeNow.toString() << std::endl;
	std::cout << "Unix Timestamp: " << dateTimeNow.toUnixTimestamp() << std::endl;

	std::cout << "\nTesting std::format support:" << std::endl;
	std::cout << std::format("Formatted DateTime (\"%Y-%m-%d %H:%M:%S\"): {}", dateTimeNow) << std::endl;

	std::cout << "\n\n\n";
	return 0;
}
