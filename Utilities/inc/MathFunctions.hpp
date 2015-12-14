#ifndef _MATHFUNCTIONS_HPP
#define _MATHFUNCTIONS_HPP 

#include <vector>
#include <stddef.h>

namespace MathFunctions
{

	template<class T>
	inline std::vector<T> linspace(T minValue, T maxValue, size_t step)
	{
		std::vector<T> result;
		T delta = (maxValue - minValue) / step;
		for(size_t i=0;i<=step;i++)
		{
			result.push_back(minValue + i*delta);
		}
		return result;
		
	}

}
#endif
