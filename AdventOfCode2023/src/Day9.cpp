#include "Day9.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Day9_Run_1()
{
	typedef long long int ll;

	std::ifstream file("res/Day9.txt");
	std::string line;

	ll sum = 0;

	while (std::getline(file, line))
	{
		std::vector<ll> history;
		ll n = 0;
		bool nSet = false;
		bool negative = false;

		for (size_t i = 0; i < line.size() + 1; i++)
		{
			if (std::isdigit(line[i]))
			{
				n = n * 10 + (ll)(line[i] - '0');
				nSet = true;
			}
			else if (line[i] == '-')
			{
				negative = true;
			}
			else
			{
				if (nSet)
				{
					ll sign = negative ? -1 : 1;

					history.push_back(n * sign);
				}

				n = 0;
				nSet = false;
				negative = false;
			}
		}

		std::vector<std::vector<ll>> v;
		std::vector<ll> tmp = history;
		std::vector<ll> newTmp;

		v.push_back(tmp);

		while (true)
		{
			bool shouldBreak = true;

			for (size_t i = 0; i < tmp.size() - 1; i++)
			{
				ll diff = tmp[i + 1] - tmp[i];

				newTmp.push_back(diff);

				if (diff != 0)
				{
					shouldBreak = false;
				}
			}

			v.push_back(newTmp);

			tmp = newTmp;

			newTmp.clear();

			if (shouldBreak)
			{
				break;
			}
		}

		ll nextVal = 0;

		for (int i = v.size() - 1 - 1; i >= 0; i--)
		{
			nextVal = v[i][v[i].size() - 1] + nextVal;
		}

		sum += nextVal;
	}

	std::cout << "Day9 Run 1 Result: " << sum << std::endl;

	file.close();
}


void Day9_Run_2()
{
	typedef long long int ll;

	std::ifstream file("res/Day9.txt");
	std::string line;

	ll sum = 0;

	while (std::getline(file, line))
	{
		std::vector<ll> history;
		ll n = 0;
		bool nSet = false;
		bool negative = false;

		for (size_t i = 0; i < line.size() + 1; i++)
		{
			if (std::isdigit(line[i]))
			{
				n = n * 10 + (ll)(line[i] - '0');
				nSet = true;
			}
			else if (line[i] == '-')
			{
				negative = true;
			}
			else
			{
				if (nSet)
				{
					ll sign = negative ? -1 : 1;

					history.push_back(n * sign);
				}

				n = 0;
				nSet = false;
				negative = false;
			}
		}

		std::vector<std::vector<ll>> v;
		std::vector<ll> tmp = history;
		std::vector<ll> newTmp;

		v.push_back(tmp);

		while (true)
		{
			bool shouldBreak = true;

			for (size_t i = 0; i < tmp.size() - 1; i++)
			{
				ll diff = tmp[i + 1] - tmp[i];

				newTmp.push_back(diff);

				if (diff != 0)
				{
					shouldBreak = false;
				}
			}

			v.push_back(newTmp);

			tmp = newTmp;

			newTmp.clear();

			if (shouldBreak)
			{
				break;
			}
		}

		ll prevVal = 0;

		for (int i = v.size() - 1 - 1; i >= 0; i--)
		{
			prevVal = v[i][0] - prevVal;
		}

		sum += prevVal;
	}

	std::cout << "Day9 Run 2 Result: " << sum << std::endl;

	file.close();
}