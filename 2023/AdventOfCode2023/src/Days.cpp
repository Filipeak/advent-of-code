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

ull Min(ull a, ull b)
{
	return a > b ? b : a;
}

ull Max(ull a, ull b)
{
	return a > b ? a : b;
}

std::vector<std::string> SplitString(std::string str, std::string delimiter)
{
	size_t pos_start = 0, pos_end = 0, delim_len = delimiter.length();

	std::string token;
	std::vector<std::string> res;

	while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos)
	{
		token = str.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(str.substr(pos_start));

	return res;
}

#ifdef _WIN32
#define OPEN_PROCESS _popen
#define CLOSE_PROCESS _pclose
#else
#define OPEN_PROCESS popen
#define CLOSE_PROCESS pclose
#endif

std::string ExecuteCommand(std::string cmd)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&CLOSE_PROCESS)> pipe(OPEN_PROCESS(cmd.c_str(), "r"), CLOSE_PROCESS);

	if (!pipe)
	{
		return "";
	}

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
	{
		result += buffer.data();
	}

	return result;
}