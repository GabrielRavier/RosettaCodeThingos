#ifndef FACTORIAL_HPP_INCLUDED
#define FACTORIAL_HPP_INCLUDED

#include <boost/iterator/counting_iterator.hpp>
#include <algorithm>
#include <numeric>

template <typename T> T factorial(T n)
{
	return std::accumulate(boost::counting_iterator<int>(1), boost::counting_iterator<int>(n + 1), 1, std::multiplies<int>());
}

#endif