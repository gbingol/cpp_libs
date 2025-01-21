#pragma once

#include <math.h>
#include <string_view>
#include <stdexcept>


inline int CharToInt(char c)
{
	return int(c)-int('0');
}



template<typename T>
inline T tonumber(std::string_view s)
{
	/*
		State Diagram is taken from:
		Aho AV, Lam MS, Sethi R. 2006. Compilers: Principles, Techniques, and Tools (2nd Edition), 
		pp 133, Figure 3.16
	*/

	//12.3E-5,  significand=12.3
	T significand{}, exponent{}; 

	int factor = 10;
	T DotFactor{1.0};

	//Sign of exponent and significand, By default positive
	std::int8_t SignExpon{1}, SignSgnf{1};

	int i=0;

	int state=12;
	while(i<s.length()) {
		switch(state) 
		{
		case 12:
			if(isdigit(s[i])) 
			{
				state=13; 
				break;
			}
			if(s[i] == '-') 
				SignSgnf = -1;
			i++;
			break;

		case 13: //It is a digit
			if(isdigit(s[i]))
			{
				state=13;
				significand = significand*factor+CharToInt(s[i]);
				i++;
			}
			else if(s[i]=='.') 
			{
				state=14;
				i++; 
			}
			else if(s[i]=='E' || s[i]=='e') 
			{
				state=16;
				i++; 
			}
			else
				state=21; //error
			break;

		case 14: // it is a dot
			state = isdigit(s[i]) ? 15 : 21;
			break;

		case 15:
			DotFactor /= 10;
			if(isdigit(s[i]))
			{
				state=15;
				significand=significand + CharToInt(s[i])*DotFactor;
				i++;
			}
			else if(s[i]=='E') 
			{
				state=16;
				i++;
			}
			else
				state=21;
			break;

		case 16: //Exponent
			if(isdigit(s[i])) 
				state=18;
			else if((s[i])=='+') 
			{
				state=17;
				i++; 
			}
			else if((s[i])=='-')
			{
				state=17; 
				SignExpon=-1;
				i++;
			}
			else 
				state=21; //error
			break;

		case 17:
			state = isdigit(s[i]) ? 18 : 21;
			break;
		case 18:
			if(isdigit(s[i]))
			{
				state=18;
				exponent=exponent*factor+CharToInt(s[i]);
				i++;
			}
			else 
				state=21;
			break;
		case 21:
			throw std::runtime_error("Error in parsing number.");
		}
	}

	return SignSgnf*significand*pow(10.0, SignExpon*exponent);
}

