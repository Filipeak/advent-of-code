#include "Day4.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void Day4_Run_1()
{
	std::ifstream file("res/Day4.txt");
	std::string line;

	int sum = 0;

	while (std::getline(file, line))
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

	std::cout << "Day4 Run 1 Result: " << sum << std::endl;

	file.close();
}

void Day4_Run_2()
{
	std::ifstream file("res/Day4.txt");
	std::string line;

	int sum = 0;
	size_t ind = 1;

	std::unordered_map<int, int> additionalCards;

	while (std::getline(file, line))
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

	std::cout << "Day4 Run 2 Result: " << sum << std::endl;

	file.close();
}