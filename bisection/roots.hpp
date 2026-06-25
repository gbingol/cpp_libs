#pragma once

#include <string>
#include <functional>
#include <type_traits>
#include <concepts>

#include "result.h"

template <typename T>
concept Real = std::is_floating_point_v<T>;
 

template <Real T>
struct bisect_res
{
	T Root;
	T Error;
	size_t NIter;
};



template <Real T>
Result<bisect_res<T>, std::string> bisection_bf(const std::function<T(T)>& func,
	T a,
	T b,
	T TOLERANCE,
	size_t MAXITERATIONS)
{		
	if (b<=a)
		return {Err, "b>a is expected."};

	size_t NIter = 0;
	auto Error = b - a;

	auto XX = a, YY = b;
	auto F_XX = func(XX), F_YY = func(YY);

	if (F_XX * F_YY > 0)
		return {Err,"Func has same sign at both bounds."};

	if (std::abs(F_XX) < TOLERANCE)
		return {Ok, bisect_res<T>{ XX, std::abs(F_XX), NIter } };

	else if (std::abs(F_YY) < TOLERANCE)
		return {Ok, bisect_res<T>{ YY, std::abs(F_YY), NIter } };


	T Xn{}, F_Xn{};
	do
	{
		NIter++;

		Xn = (XX + YY) * static_cast<T>(0.5);

		F_Xn = func(Xn);

		if (std::abs(F_Xn) < TOLERANCE)
			return {Ok, bisect_res<T>{ Xn, std::abs(F_Xn), NIter} };

		auto test = F_Xn * F_XX;
		if (test < 0.0)
			YY = Xn;
		else
		{
			XX = Xn;
			F_XX = F_Xn;
		}

		if (NIter >= MAXITERATIONS)
			return {Err, "Max iters exceeded."};

		Error = std::abs(YY-XX);

	} while ((Error > TOLERANCE));

	return {Ok, bisect_res<T>{ Xn, Error, NIter}};
}