#include "../Days.h"

DEFINE_FUNCTION_FOR_DAY(4, 1)
{
	GET_LINES(4);

	int sum = 0;

	for (const auto& line : lines)
	{
		std::vector<int> winningNumbers;
		std::vector<int> numbers;

		int n = 0;
		bool check = false;

		for (size_t i = line.find(":"); i < line.size() + 1; i++)
		{
			if (line[i] == '|')
			{
				check = true;
			}

			if (std::isdigit(line[i]))
			{
				n = n * 10 + (int)(line[i] - '0');
			}
			else
			{
				if (n != 0)
				{
					if (!check)
					{
						winningNumbers.push_back(n);
					}
					else
					{
						numbers.push_back(n);
					}

					n = 0;
				}
			}
		}

		int points = 0;

		for (size_t i = 0; i < winningNumbers.size(); i++)
		{
			for (size_t j = 0; j < numbers.size(); j++)
			{
				if (winningNumbers[i] == numbers[j])
				{
					if (points == 0)
					{
						points = 1;
					}
					else
					{
						points *= 2;
					}

					break;
				}
			}
		}

		sum += points;
	}

	return sum;
}

DEFINE_FUNCTION_FOR_DAY(4, 2)
{
	GET_LINES(4);

	int sum = 0;
	size_t ind = 1;

	std::unordered_map<int, int> additionalCards;

	for (const auto& line : lines)
	{
		std::vector<int> winningNumbers;
		std::vector<int> numbers;

		int n = 0;
		bool check = false;

		for (size_t i = line.find(":"); i < line.size() + 1; i++)
		{
			if (line[i] == '|')
			{
				check = true;
			}

			if (std::isdigit(line[i]))
			{
				n = n * 10 + (int)(line[i] - '0');
			}
			else
			{
				if (n != 0)
				{
					if (!check)
					{
						winningNumbers.push_back(n);
					}
					else
					{
						numbers.push_back(n);
					}

					n = 0;
				}
			}
		}

		int count = 0;

		for (size_t i = 0; i < winningNumbers.size(); i++)
		{
			for (size_t j = 0; j < numbers.size(); j++)
			{
				if (winningNumbers[i] == numbers[j])
				{
					count++;

					break;
				}
			}
		}

		for (size_t i = 1; i <= count; i++)
		{
			additionalCards[ind + i]++;

			for (size_t j = 0; j < additionalCards[ind]; j++)
			{
				additionalCards[ind + i]++;
			}
		}

		sum += additionalCards[ind] + 1;

		ind++;
	}

	return sum;
}