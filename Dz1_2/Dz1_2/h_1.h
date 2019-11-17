#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <iterator>
#include <functional>
#include <ctime>

//Use Ctrl+M+L

bool createDataByStream(const std::string& filename)
{
	srand(time(0));
	std::ofstream fout(filename + ".txt");
	if (fout.is_open())
	{
		for (int i = 0; i < 100; i++)
			fout << rand() % 101 - 50 << std::endl;
		fout.close();
		return 1;
	}
	else
		return 0;
}


bool createDataByGenerate(const std::string& filename)
{
	srand((int)time(0));
	std::ofstream fout(filename + ".txt");
	if (fout.is_open())
	{
		std::list<int> list;
		list.resize(100);
		std::generate(list.begin(), list.end(), [] {return rand() % 101 - 50; });
		std::copy(list.begin(), list.end(), std::ostream_iterator<int>(fout, "\n"));
		fout.close();
		return 1;
	}
	else
		return 0;
}

template<typename T>
bool loadData1(const std::string& filename, T& container)
{
	std::ifstream fin(filename + ".txt");
	if (fin.is_open())
	{
		int temp;
		while (fin >> temp)
			container.push_back(temp);
		fin.close();
		return 1;
	}
	else
		return 0;
}

template<typename T>
bool loadData2(const std::string& filename, T& container)
{
	std::ifstream fin(filename + ".txt");
	if (fin.is_open())
	{
		std::istream_iterator<int> input(fin);
		std::istream_iterator<int> end_of_stream;
		copy(input, end_of_stream, inserter(container, container.begin()));
		fin.close();
		return 1;
	}
	else
		return 0;
}

template<typename T>
T modify(T& container)
{
	int sum = 0;
	for (auto cur : container) {
		if (cur < 0)
			sum = abs(cur) / 2;
	}
	T result(container);
	for (auto cur = result.begin(); cur != result.end(); cur++)
		*cur += sum / 2;
	result.push_back(sum);
	return result;
}

template<typename T>
std::list<int> modify(T beg, T end)
{
	int sum = 0;
	for (T i = beg; i != end; i++) {
		if (*i < 0)
			sum = abs(*i) / 2;
	}

	std::list<int> result(beg, end);
	for (auto cur = result.begin(); cur != result.end(); cur++)
		*cur += sum;
	result.push_back(sum);
	return result;
}


template<typename T>
void modify(T& container, std::function<void(int&)> func)
{
	std::for_each(container.begin(), container.end(), func);
}

void modify(const std::string& filename, const std::string& resultFilename, std::function<int(const int&)> func)
{
	std::ofstream fout(resultFilename + ".txt");
	std::ifstream fin(filename + ".txt");
	std::istream_iterator<int> input(fin);
	std::ostream_iterator<int> output(fout, "\n");
	std::istream_iterator<int> end_of_stream;
	std::transform(input, end_of_stream, output, func);
	fin.close();
	fout.close();
}


bool outputResult1(const std::string& filename)
{
	std::ifstream fin(filename + ".txt");
	if (fin.is_open())
	{
		int temp;
		while (fin >> temp)
			std::cout << temp << "  ";
		std::cout << std::endl;
		fin.close();
		return 1;
	}
	else
		return 0;
}

template<typename T>
void outputResult2(T& container, const std::string& filename)
{
	std::ofstream fout(filename + ".txt");
	copy(container.begin(), container.end(), std::ostream_iterator<int>(fout, "\n"));
	fout.close();
}
