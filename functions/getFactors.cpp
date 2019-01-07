#include <vector>
#include <cstdint>
#include <algorithm>

using std::vector;
using std::sort;

vector<uint32_t> getFactors(uint32_t n)
{
	vector<uint32_t> result;
	
	result.push_back(1);
	result.push_back(n);
	
	for (uint32_t i = 2; i * i <= n; ++i)
	{
		if (!(n % i))
		{
			result.push_back(i);
			if (i * i != n)
				result.push_back(n / i);
		}
	}
	
	sort(result.begin(), result.end());
}