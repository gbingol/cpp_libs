#include <iostream>

#include "number.h"

#define CONVERT(x, expr, FLOAT) \
	f = tonumber<FLOAT>(x); \
	std::cout << expr << std::endl;

int main()
{
	double f;
	CONVERT("12.3", 2*f, decltype(f));
	CONVERT("1E-5", 2*f, decltype(f));
	CONVERT("1.25E-1", 4*f, decltype(f));
	CONVERT("1.25E1", 4*f, decltype(f));
	CONVERT("1.25E001", 4*f, decltype(f));
	CONVERT("-1.25E-1", 10*f, decltype(f));
	

	// The following will cause error
	try 
	{
		CONVERT("0.1250E2.2", 4*f, decltype(f));
		CONVERT("1.E25E001", 4*f, decltype(f));
	} 
	catch (const std::runtime_error& e) 
	{
		std::cout << e.what() << std::endl;
	}
	
}