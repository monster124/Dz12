#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <iterator>
#include <functional>
#include <ctime>
#include <iomanip>
#include <map>
#include <string>
#include <utility>
#include <unordered_set>
#include <string>
#include <stdio.h>
#include <algorithm>

//Use Ctrl+M+L
struct Luggage
{
	int fly_number;
	std::string date;
	std::string time;
	std::string arr_city;
	std::string surname;
	int lug_count;
	std::string lug_weight;

	bool operator==(const Luggage& second_lug) const
	{
		return (second_lug.fly_number == fly_number &&
			std::string(second_lug.date) == std::string(date) &&
			std::string(second_lug.time) == std::string(time) &&
			std::string(second_lug.arr_city) == std::string(arr_city) &&
			std::string(second_lug.surname) == std::string(surname) &&
			second_lug.lug_count == lug_count &&
			std::string(second_lug.lug_weight) == std::string(lug_weight));
	}

	friend std::ostream& operator << (std::ostream& p_out, const Luggage& second_lug)
	{
		p_out
			<< std::setw(5) << std::left << second_lug.fly_number
			<< std::setw(12) << std::left << second_lug.date
			<< std::setw(8) << std::left << second_lug.time
			<< std::setw(15) << std::left << second_lug.arr_city
			<< std::setw(20) << std::left << second_lug.surname
			<< std::setw(3) << std::left << second_lug.lug_count
			<< std::setw(5) << std::left << second_lug.lug_weight << std::endl;
		return p_out;
	}
};

namespace std
{
	template<> struct hash<Luggage>
	{
		std::size_t operator()(Luggage const& d) const noexcept
		{
			std::size_t seed = d.fly_number;
			seed ^= stdext::hash_value(d.date) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= stdext::hash_value(d.time) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= stdext::hash_value(d.arr_city) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= stdext::hash_value(d.surname) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= stdext::hash_value(d.lug_count) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			seed ^= stdext::hash_value(d.lug_weight) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};
}


std::map<int, Luggage> Lug_map;
std::unordered_set<Luggage> Lug_unordered_set;

bool createLugDatabase(const std::string& filename)
{
	std::fstream fout(filename + ".bin", std::ios::binary | std::ios::out);
	if (fout.is_open()) {
		Luggage new_lug;
		int exit;
		do {
			std::cout << "Enter fly number: ";
			std::cin >> new_lug.fly_number;
			std::cout << std::endl;
			std::cout << "Enter date: ";
			std::cin >> new_lug.date;
			std::cout << std::endl;
			std::cout << "Enter time: ";
			std::cin >> new_lug.time;
			std::cout << std::endl;
			std::cout << "Enter arrival city: ";
			std::cin >> new_lug.arr_city;
			std::cout << std::endl;
			std::cout << "Enter surname: ";
			std::cin >> new_lug.surname;
			std::cout << std::endl;
			std::cout << "Enter count of luggage: ";
			std::cin >> new_lug.lug_count;
			std::cout << std::endl;
			std::cout << "Enter weight of luggage: ";
			std::cin >> new_lug.lug_weight;
			std::cout << std::endl;

			if (Lug_unordered_set.empty() || Lug_unordered_set.find(new_lug) == Lug_unordered_set.end())
			{
				Lug_unordered_set.insert(new_lug);
				Lug_map.insert(std::pair<int, Luggage>(new_lug.fly_number, new_lug));
				fout.write(reinterpret_cast <char*>(&new_lug), sizeof(Luggage));
			}
			else
			{
				std::cout << "Error." << std::endl;
			}

			std::cout << " 0 - final programm, 1 - continue  : ";
			std::cin >> exit;

		} while (exit != 0);
		fout.close();
		return 1;
	}
	else
		return 0;
}


bool addToLugDatabase(const std::string& filename)
{
	if (Lug_unordered_set.empty()) {
		std::fstream fin(filename + ".bin", std::ios::binary | std::ios::in);
		if (fin.is_open()) {
			Luggage cur_lug;
			while (fin.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))
				Lug_unordered_set.insert(cur_lug);
			fin.close();
		}
	}
	int m;
	std::cout << "pick 1 to add luggage: ";
	std::cin >> m;
	if (m == 1)
	{
		std::fstream fout(filename + ".bin", std::ios::binary | std::ios::app);
		if (fout.is_open())
		{
			Luggage new_lug;
			int exit;
			do
			{
				std::cout << "\n Add new Luggage: " << std::endl;
				std::cout << "Enter fly number: ";
				std::cin >> new_lug.fly_number;
				std::cout << std::endl;
				std::cout << "Enter date: ";
				std::cin >> new_lug.date;
				std::cout << std::endl;
				std::cout << "Enter time: ";
				std::cin >> new_lug.time;
				std::cout << std::endl;
				std::cout << "Enter arrival city: ";
				std::cin >> new_lug.arr_city;
				std::cout << std::endl;
				std::cout << "Enter surname: ";
				std::cin >> new_lug.surname;
				std::cout << std::endl;
				std::cout << "Enter count of luggage: ";
				std::cin >> new_lug.lug_count;
				std::cout << std::endl;
				std::cout << "Enter weight of luggage: ";
				std::cin >> new_lug.lug_weight;
				std::cout << std::endl;

				if (Lug_unordered_set.empty() || Lug_unordered_set.find(new_lug) == Lug_unordered_set.end())
				{
					Lug_unordered_set.insert(new_lug);
					Lug_map.insert(std::pair<int, Luggage>(new_lug.fly_number, new_lug));
					fout.write(reinterpret_cast <char*>(&new_lug), sizeof(Luggage));
				}
				else
				{
					std::cout << "Error." << std::endl;
				}

				std::cout << " 0 - final programm, 1 - continue  : ";
				std::cin >> exit;

			} while (exit != 0);
			fout.close();
			return 1;
		}
		else
			return 0;
	}
}


bool convertToTxt(const std::string& filename)
{
	std::ifstream fin(filename + ".bin", std::ios::binary);
	std::ofstream fout(filename + ".txt");
	if (fin.is_open())
	{
		Luggage cur_product;
		while (fin.read(reinterpret_cast <char*>(&cur_product), sizeof(Luggage)))
			fout << cur_product;
		fin.close();
		fout.close();
		return 1;
	}
	else
	{
		std::cout << "Ð¤Ð°Ð¹Ð» " + filename + " Ð½Ðµ ÑƒÐ´Ð°Ð»Ð¾ÑÑŒ Ð¾Ñ‚ÐºÑ€Ñ‹Ñ‚ÑŒ." << std::endl;
		return 0;
	}
}

std::string findByNumber(const std::string& filename, const int num)
{
	std::fstream fin(filename + ".bin", std::ios::binary | std::ios::in);
	std::string a(filename + "_fly_number");
	std::fstream fout(a + ".bin", std::ios::binary | std::ios::out);
	int founded = 0;
	if (fin.is_open())
	{
		Luggage cur_lug;
		while (fin.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))
			if (cur_lug.fly_number == num)
			{
				fout.write(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage));
				founded++;
			}
	}
	fin.close();
	fout.close();
	if (founded)
		return a;
	else {
		remove((a + ".bin").c_str());
		return "Error";
	}
}


std::string findByCity(const std::string& filename, const std::string& city)
{
	std::fstream fin(filename + ".bin", std::ios::binary | std::ios::in);
	std::string a(filename + "_arr_city");
	std::fstream fout(a + ".bin", std::ios::binary | std::ios::out);
	int founded = 0;
	if (fin.is_open())
	{
		Luggage cur_lug;
		while (fin.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))
			if (cur_lug.arr_city == city)
			{
				fout.write(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage));
				founded++;
			}
		fin.close();
		fout.close();
	}
	convertToTxt(a);
	if (founded)
		return a;
	else {
		remove((a + ".bin").c_str());
		return "Error";
	}
}

std::string findByWeight(const std::string& filename, const std::string& weight)
{
	std::fstream fin(filename + ".bin", std::ios::binary | std::ios::in);
	std::string a(filename + "_arr_city");
	std::fstream fout(a + ".bin", std::ios::binary | std::ios::out);
	int founded = 0;
	if (fin.is_open())
	{
		Luggage cur_lug;
		while (fin.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))
			if (stof(cur_lug.lug_weight) > stof(weight))
			{
				fout.write(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage));
				founded++;
			}
		convertToTxt(a);
		fin.close();
		fout.close();
	}
	if (founded)
		return a;
	else {
		remove((a + ".bin").c_str());
		return "Error";
	}
}


std::string findByDate(const std::string& filename, const std::string& date)
{
	std::fstream fin(filename + ".bin", std::ios::binary | std::ios::in);
	std::string a(filename + "_date");
	std::fstream fout(a + ".bin", std::ios::binary | std::ios::out);
	int founded = 0;
	if (fin.is_open())
	{
		Luggage cur_lug;
		while (fin.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))
			if (cur_lug.date == date)
			{
				fout.write(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage));
				founded++;
			}
		fin.close();
		fout.close();
	}
	convertToTxt(a);
	if (founded)
		return a;
	else {
		remove((a + ".bin").c_str());
		return "Error";
	}
}


void removeLugs(const std::string& filename, const std::string& removable)
{
	std::fstream fin(filename + ".bin", std::ios::binary | std::ios::in);
	std::fstream fin_rem(removable + ".bin", std::ios::binary | std::ios::in);
	std::unordered_set<Luggage> removable_lug;
	if (fin_rem.is_open())
	{
		Luggage cur_lug;
		while (fin_rem.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))
			removable_lug.insert(cur_lug);
		fin_rem.close();
	}

	std::fstream fout(filename + "_temporarity.bin", std::ios::binary | std::ios::out);

	if (fin.is_open()) {

		Luggage cur_lug;
		while (fin.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))

			if (removable_lug.find(cur_lug) == removable_lug.end()) {
				fout.write(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage));
			}

		fin.close();
		fout.close();
	}

	remove((filename + ".bin").c_str());
	rename((filename + "_temporarity.bin").c_str(), (filename + ".bin").c_str());
	remove((filename + "_temporarity.bin").c_str());
}


void replaceLugs(const std::string& filename, const std::string& replaceble)
{
	std::fstream fin(filename + ".bin", std::ios::binary | std::ios::in);
	std::fstream fin_rem(replaceble + ".bin", std::ios::binary | std::ios::in);
	std::unordered_set<Luggage> removable_lug;
	if (fin_rem.is_open())
	{
		Luggage cur_lug;
		while (fin_rem.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))
			removable_lug.insert(cur_lug);
		fin_rem.close();
	}

	std::fstream fout(filename + "_temporarity.bin", std::ios::binary | std::ios::out);

	if (fin.is_open())
	{
		Luggage cur_lug;
		while (fin.read(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage)))
			if (removable_lug.find(cur_lug) == removable_lug.end())
				fout.write(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage));
			else
			{
				std::cout << "Luggage: ";
				std::cout << cur_lug.fly_number << std::endl;;
				std::cout << cur_lug.date << std::endl;
				std::cout << cur_lug.time << std::endl;
				std::cout << cur_lug.arr_city << std::endl;
				std::cout << cur_lug.surname << std::endl;
				std::cout << cur_lug.lug_count << std::endl;
				std::cout << cur_lug.lug_weight << std::endl;
				fout.write(reinterpret_cast <char*>(&cur_lug), sizeof(Luggage));
			}
		fin.close();
		fout.close();
	}
	remove((filename + ".bin").c_str());
	rename((filename + "_temporarity.bin").c_str(), (filename + ".bin").c_str());
	remove((filename + "_temporarity.bin").c_str());
}