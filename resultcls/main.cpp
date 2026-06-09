#include <iostream>

#include "result.h"

Result<double, const char*> compute(double x)
{
	if(x>5)
		return {Ok, x};

	return {Err, "Error happenend"};
}




struct BisectResult{
	std::size_t iter;
	double root;
};


Result<BisectResult, const char*> FindRoot(double f)
{
	if(std::abs(f) <= 1E-6)
		return {Ok, BisectResult{20, 1.44}};

	return {Err, "No root found"};
}


/******************************************** */

int main() {

	auto res = compute(7);
	if(const auto x = res.get_if())
		std::cout << *x;
	else
		std::cout << res.err();

	std::cout<<std::endl;
	
	auto root = FindRoot(0.0);
	if(const auto r = root.get_if())
		std::cout<<"Root="<<r->root <<" iter="<<r->iter;
	else
		std::cout<<root.err();
}