#pragma once

#include <chrono>
#include <iostream>
#include <string_view>


//
class SimpleTimer 
{
public:
	using ClockType = std::chrono::high_resolution_clock;

	SimpleTimer(std::string_view funcname) : 
		m_funcname{funcname}, 
		m_start{ClockType::now()} {}

	SimpleTimer(const SimpleTimer&) = delete;
	
	SimpleTimer(SimpleTimer&&) = delete;
	
	SimpleTimer& operator=(const SimpleTimer&) = delete;
	
	SimpleTimer& operator=(SimpleTimer&&) = delete;
	
	~SimpleTimer() 
	{
		using namespace std::chrono;
		auto duration = duration_cast<microseconds>(ClockType::now() - m_start).count();
		
		std::cout << duration << " micro_sec " << m_funcname << '\n';
	}
private:
	std::string_view m_funcname{};
	const ClockType::time_point m_start{};
};