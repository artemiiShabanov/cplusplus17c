#pragma once

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <time.h>
#include <functional>
#include <vector>


using std::tr1::function;

//Helpers

int get_max(std::list<int> list)
{
	if (list.empty()) throw "Empty list";

	int max = list.front();
	for (int x : list)
	{
		if (x > max) max = x;
	}
	return max;
}

int get_max_iter(std::list<int>::iterator begin, std::list<int>::iterator end)
{
	if (begin == end) throw "Empty list";

	int max = *begin;
	for (auto it = begin; it != end; it++)
	{
		if (*it > max) max = *it;
	}
	return max;
}

auto lambda_gen = [](int max) -> function<int(int)>
{
	return [max](int x) -> int { return x > 0? max : x; };
};




//1

std::fstream random_fill_file_cicle(std::string file_name, int N, int M)
{
	srand(time(NULL));
	std::fstream fout(file_name, std::ios::out);
	for (int i = 0; i < N; i++)
	{
		fout << (rand() % (2 * M) + 1) - M << "\n";
	}
	fout.close();
	return fout;
}

std::fstream random_fill_file_generate(std::string fileName, int N, int M)
{
	std::vector<int> v(N);
	std::fstream fout(fileName, std::ios::out);
	std::generate(v.begin(), v.end(), rand);
	for (int i = 0; i < N; i++)
	{
		fout << (v[i] % (2 * M) + 1) - M << "\n";
	}
	fout.close();
	return fout;
}




//2

std::list<int> get_list_from_file(std::string file_name)
{
	std::list<int> list;
	int x;
	std::fstream fin(file_name, std::ios::in);
	while (fin >> x)
	{
		list.push_back(x);
	}
	fin.close();
	return list;
}

//3

std::list<int> modify(std::list<int> list)
{
	try
	{
		int max = get_max(list);
		for (auto it = list.begin(); it != list.end(); it++)
		{
			if (*it > 0) *it = max;
		}
		return list;
	}
	catch(std::string e)
	{
		std::cout << e << std::endl;
		return list;
	}	
}

//4

void modify_range(std::list<int>::iterator begin, std::list<int>::iterator end)
{
	/*std::list<int> list;
	for (auto it = begin; it != end; it++)
	{
		list.push_back(*it);
	}
	list = modify(list);
	return list;
	*/
	
	std::list<int> list_out;
	try
	{
		int max = get_max_iter(begin, end);
		for (auto it = begin; it != end; it++)
		{
			*it = *it > 0 ? max : *it;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}
}

//5

std::list<int> modify_transform(std::list<int> list_in)
{
	try
	{
		int max = get_max(list_in);
		std::list<int> list_out;
		list_out.resize(list_in.size());

		std::transform(list_in.begin(), list_in.end(), list_out.begin(), lambda_gen(max));
		return list_out;
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
		return list_in;
	}
}
 
//6

std::list<int> modify_foreach(std::list<int> list_in)
{
	try
	{
		int max = get_max(list_in);

		std::for_each(list_in.begin(), list_in.end(), [max](int &x) -> void { if (x > 0) x = max; });
		return list_in;
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
		return list_in;
	}
}

//7

int list_sum(std::list<int> &list)
{
	int sum = 0;
	for (int x: list)
	{
		sum += x;
	}
	return sum;
}

double list_average(std::list<int> &list)
{
	return (double)list_sum(list)/list.size();
}


//8

void output_list_file(std::list<int> &list, std::string file_name = "")
{	
	std::fstream fout(file_name, std::ios::out);
	for (int x : list)
	{
		fout << x << std::endl;;
	}
	fout.close();
}

void output_list_console(std::list<int> &list)
{
	for (int x : list)
	{
		std::cout << x << " -> ";
	}
	std::cout << std::endl;
}
