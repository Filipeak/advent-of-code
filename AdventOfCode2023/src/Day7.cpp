#include "Day7.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void Day7_Run_1()
{
	struct Hand
	{
		std::string cards;
		int type;
		int bid;
	};
	std::unordered_map<char, int> strengths = {
		{'A',13},
		{'K',12},
		{'Q',11},
		{'J',10},
		{'T',9},
		{'9',8},
		{'8',7},
		{'7',6},
		{'6',5},
		{'5',4},
		{'4',3},
		{'3',2},
		{'2',1},
	};

	std::ifstream file("res/Day7.txt");
	std::string line;

	std::vector<Hand> hands;

	while (std::getline(file, line))
	{
		std::unordered_map<char, int> ch;
		std::string cards;
		bool isSpace = false;
		int bid = 0;

		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ')
			{
				isSpace = true;
			}
			else if (!isSpace)
			{
				ch[line[i]]++;
				cards += line[i];
			}
			else
			{
				bid = bid * 10 + (int)(line[i] - '0');
			}
		}

		int type = 7;

		for (const auto& c1 : ch)
		{
			if (c1.second == 5)
			{
				type = 1;

				break;
			}
			else if (c1.second == 4)
			{
				type = 2;

				break;
			}
			else if (c1.second == 3)
			{
				for (const auto& c2 : ch)
				{
					if (c2.first != c1.first)
					{
						if (c2.second == 2)
						{
							type = 3;
						}
						else
						{
							type = 4;
						}

						break;
					}
				}

				break;
			}
			else if (c1.second == 2)
			{
				bool valid = false;

				for (const auto& c2 : ch)
				{
					if (c2.first != c1.first)
					{
						if (c2.second == 3)
						{
							type = 3;

							valid = true;

							break;
						}
						else if (c2.second == 2)
						{
							type = 5;

							valid = true;

							break;
						}
					}
				}

				if (!valid)
				{
					type = 6;
				}

				break;
			}
		}

		hands.push_back({ cards,type,bid });
	}

	for (size_t i = 0; i < hands.size() - 1; i++)
	{
		for (size_t j = 0; j < hands.size() - i - 1; j++)
		{
			if (hands[j].type < hands[j + 1].type)
			{
				Hand h = hands[j + 1];
				hands[j + 1] = hands[j];
				hands[j] = h;
			}
		}
	}

	for (size_t i = 0; i < hands.size() - 1; i++)
	{
		for (size_t j = 0; j < hands.size() - i - 1; j++)
		{
			bool valid = false;

			if (hands[j].type == hands[j + 1].type)
			{
				for (size_t k = 0; k < hands[j].cards.size(); k++)
				{
					if (strengths[hands[j].cards[k]] != strengths[hands[j + 1].cards[k]])
					{
						valid = strengths[hands[j].cards[k]] > strengths[hands[j + 1].cards[k]];

						break;
					}
				}
			}

			if (valid)
			{
				Hand h = hands[j + 1];
				hands[j + 1] = hands[j];
				hands[j] = h;
			}
		}
	}

	int sum = 0;

	for (size_t i = 0; i < hands.size(); i++)
	{
		sum += hands[i].bid * (i + 1);
	}

	std::cout << "Day7 Run 1 Result: " << sum << std::endl;

	file.close();
}

void Day7_Run_2()
{
	struct Hand
	{
		std::string cards;
		int type;
		int bid;
	};
	std::unordered_map<char, int> strengths = {
		{'A',13},
		{'K',12},
		{'Q',11},
		{'T',10},
		{'9',9},
		{'8',8},
		{'7',7},
		{'6',6},
		{'5',5},
		{'4',4},
		{'3',3},
		{'2',2},
		{'J',1},
	};

	std::ifstream file("res/Day7.txt");
	std::string line;

	std::vector<Hand> hands;

	while (std::getline(file, line))
	{
		std::unordered_map<char, int> ch;
		std::string cards;
		bool isSpace = false;
		int bid = 0;

		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ')
			{
				isSpace = true;
			}
			else if (!isSpace)
			{
				ch[line[i]]++;
				cards += line[i];
			}
			else
			{
				bid = bid * 10 + (int)(line[i] - '0');
			}
		}

		int max = 0;
		char maxC = 'A';
		for (const auto& c : ch)
		{
			if (c.second > max && c.first != 'J')
			{
				max = c.second;
				maxC = c.first;
			}
		}

		if (ch.find('J') != ch.end())
		{
			ch[maxC] += ch['J'];
			ch.erase('J');
		}

		int type = 7;

		for (const auto& c1 : ch)
		{
			if (c1.second == 5)
			{
				type = 1;

				break;
			}
			else if (c1.second == 4)
			{
				type = 2;

				break;
			}
			else if (c1.second == 3)
			{
				for (const auto& c2 : ch)
				{
					if (c2.first != c1.first)
					{
						if (c2.second == 2)
						{
							type = 3;
						}
						else
						{
							type = 4;
						}

						break;
					}
				}

				break;
			}
			else if (c1.second == 2)
			{
				bool valid = false;

				for (const auto& c2 : ch)
				{
					if (c2.first != c1.first)
					{
						if (c2.second == 3)
						{
							type = 3;

							valid = true;

							break;
						}
						else if (c2.second == 2)
						{
							type = 5;

							valid = true;

							break;
						}
					}
				}

				if (!valid)
				{
					type = 6;
				}

				break;
			}
		}

		hands.push_back({ cards,type,bid });
	}

	for (size_t i = 0; i < hands.size() - 1; i++)
	{
		for (size_t j = 0; j < hands.size() - i - 1; j++)
		{
			if (hands[j].type < hands[j + 1].type)
			{
				Hand h = hands[j + 1];
				hands[j + 1] = hands[j];
				hands[j] = h;
			}
		}
	}

	for (size_t i = 0; i < hands.size() - 1; i++)
	{
		for (size_t j = 0; j < hands.size() - i - 1; j++)
		{
			bool valid = false;

			if (hands[j].type == hands[j + 1].type)
			{
				for (size_t k = 0; k < hands[j].cards.size(); k++)
				{
					if (strengths[hands[j].cards[k]] != strengths[hands[j + 1].cards[k]])
					{
						valid = strengths[hands[j].cards[k]] > strengths[hands[j + 1].cards[k]];

						break;
					}
				}
			}

			if (valid)
			{
				Hand h = hands[j + 1];
				hands[j + 1] = hands[j];
				hands[j] = h;
			}
		}
	}

	int sum = 0;

	for (size_t i = 0; i < hands.size(); i++)
	{
		sum += hands[i].bid * (i + 1);
	}

	std::cout << "Day7 Run 2 Result: " << sum << std::endl;

	file.close();
}