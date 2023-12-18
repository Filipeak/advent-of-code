#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(9, 1)
{
	GET_LINES(9);

	ll sum = 0;

	for (const auto& line : lines)
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

	return sum;
}


DEFINE_FUNCTION_FOR_DAY(9, 2)
{
	GET_LINES(9);

	ll sum = 0;

	for (const auto& line : lines)
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

	return sum;
}