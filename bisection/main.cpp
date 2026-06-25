#include <iostream>


#include "simpletimer.hpp"
#include "roots.hpp"
#include <cmath>


int main() {

	auto f = [](auto x)
	{ 
		using T = decltype(x);
		return std::pow(x, T{10}) - T{1.0};
	};

	SimpleTimer timer("main");

	using FLOAT = double;
	FLOAT root;
	for(std::size_t i=0; i<5000; i++)
	{
		auto res = bisect<FLOAT>(f, (FLOAT)0.0, (FLOAT)3.0, (FLOAT)1E-6, 500);
		if(auto p = res.get_if())
			root = p->Root;
	}

	//std::cout<<root <<std::endl;

	return 0;
}
