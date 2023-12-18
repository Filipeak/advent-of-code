#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <chrono>

typedef long long int ll;
typedef unsigned long long int ull;

ull GCD(ull a, ull b);
ull LCM(std::vector<ull> arr);
int HexToDec(std::string hex);

#define DECLARE_FUNCTIONS_FOR_DAY(day) ull Day_ ## day ## _Part_1(); ull Day_ ## day ## _Part_2();
#define DEFINE_FUNCTION_FOR_DAY(day, part) ull Day_ ## day ## _Part_ ## part()
#define RUN_FUNCTION_FOR_DAY(day, part) Day_ ## day ## _Part_ ## part()
#define BENCHMARK_FUNCTION(day, part) {std::cout << "> Beginning of execution of function: " "Day_" #day "_Part_" #part "()" << std::endl;auto start = std::chrono::high_resolution_clock::now();ull result = RUN_FUNCTION_FOR_DAY(day, part);auto end = std::chrono::high_resolution_clock::now();std::chrono::duration<double, std::milli> ms = end - start;std::cout <<  "   Result: " << result << std::endl;std::cout << "> Execution took: " << ms.count() << "ms\n" << std::endl;}
#define GET_LINES(day) std::vector<std::string> lines; {std::ifstream file("src/Day" #day "/in.txt");std::string line; while(std::getline(file,line)){lines.push_back(line);} file.close();}

DECLARE_FUNCTIONS_FOR_DAY(1);
DECLARE_FUNCTIONS_FOR_DAY(2);
DECLARE_FUNCTIONS_FOR_DAY(3);
DECLARE_FUNCTIONS_FOR_DAY(4);
DECLARE_FUNCTIONS_FOR_DAY(5);
DECLARE_FUNCTIONS_FOR_DAY(6);
DECLARE_FUNCTIONS_FOR_DAY(7);
DECLARE_FUNCTIONS_FOR_DAY(8);
DECLARE_FUNCTIONS_FOR_DAY(9);
DECLARE_FUNCTIONS_FOR_DAY(10);
DECLARE_FUNCTIONS_FOR_DAY(11);
DECLARE_FUNCTIONS_FOR_DAY(12);
DECLARE_FUNCTIONS_FOR_DAY(13);
DECLARE_FUNCTIONS_FOR_DAY(14);
DECLARE_FUNCTIONS_FOR_DAY(15);
DECLARE_FUNCTIONS_FOR_DAY(16);
DECLARE_FUNCTIONS_FOR_DAY(17);
DECLARE_FUNCTIONS_FOR_DAY(18);