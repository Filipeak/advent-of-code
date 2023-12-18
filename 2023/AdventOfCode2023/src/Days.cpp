#include "Days.h"

int HexToDec(std::string hex)
{
	int base = 1;
	int n = 0;

	for (int i = hex.size() - 1; i >= 0; i--)
	{
		int tmp = (hex[i] >= '0' && hex[i] <= '9') ? (hex[i] - '0') : (10 + hex[i] - 'a');

		n += tmp * base;
		base *= 16;
	}

	return n;
}

ull GCD(ull a, ull b)
{
	if (b == 0) return a;

	return GCD(b, a % b);
}

ull LCM(std::vector<ull> arr)
{
	ull ans = arr[0];

	for (size_t i = 1; i < arr.size(); i++)
	{
		ans = (((arr[i] * ans)) / (GCD(arr[i], ans)));
	}

	return ans;
}