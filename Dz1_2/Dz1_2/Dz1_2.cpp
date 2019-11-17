// Dz1_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <iterator>

#include "h_1.h"
#include "h_2.h"

int main()
{

	std::cout << "=====		Test: Part 1   ======\n\n";
	std::string file1("Part_1_First"), file2("Part_1_Second");

	std::cout << " Making of first file (stream):  /n";
	createDataByStream(file1);
	std::cout << "Making of second (generate):  /n";
	createDataByGenerate(file2);

	std::list<int> list1, list2;
	std::cout << "Making first list (1 method):  /n";
	loadData1(file1, list1);
	std::cout << "Making second list (2 method):  /n";
	loadData2(file2, list2);

	//ïåðâûå äâå ô-èè = ÇÀÌÅÍÀ ÂÑÅÕ ÍÓËÅÉ ÑÐÅÄÍÈÌ ÀÐÈÔÌÅÒÈ×ÅÑÊÈÌ
	std::cout << "\n list1 before changing:  "; for (auto i : list1) std::cout << i << "  " << std::endl;
	std::cout << "\n list1 after changing:  "; for (auto i : modify(list1)) std::cout << i << "  " << std::endl;
	std::cout << "\n Last numbers - summary and srednee arif of first list. ";
	modify(list1.begin(), list1.end());
	modify(list1, [](int& n) { n++; });	//+1 êî âñåì ÷èñëàì
	modify(file1, "Part_1_ModifiedFirst", [](const int& n) {return n - 1; });	//â ModifiedFirst âñå ÷èñëà íà 1 ìåíüøå, ÷åì â First
	std::cout << "\n\n Print of first file:  ";
	outputResult1(file1);
	std::cout << "\nPrint of changed first file (n-1):  ";
	outputResult1("Part_1_ModifiedFirst");

	//ïåðåâîä êîíòåéíåðà â ôàéë
	outputResult2(list1, "Part_1_FirstFromContainer");

	std::cout << "\nPrint file of first list (First+1):  ";
	outputResult1("Part_1_FirstFromContainer");




	//			ÒÅÑÒ: ×ÀÑÒÜ 2



	std::cout << "\n\n=====		Test: Part 2	======\n\n";
	std::string Base("Part_2_LugDatadase"), founded_by_num, founded_by_name, founded_by_date;
	//createLugDatabase(Base);		
	//addToLugDatabase(Base);	


	founded_by_num = findByNumber(Base, 320);
	if (founded_by_num != "Error")
		convertToTxt(founded_by_num);

	founded_by_name = findByCity(Base, "Moscow");
	if (founded_by_name != "Error")
		convertToTxt(founded_by_name);

	founded_by_date = findByDate(Base, "09.10.2019");
	if (founded_by_date != "Error")
		convertToTxt(founded_by_date);

	founded_by_date = findByWeight(Base, "21,1");
	if (founded_by_num != "Error")
		convertToTxt(founded_by_date);

	if (founded_by_num != "Error")
		removeLugs(Base, founded_by_num); //óäàëåíèå 
	convertToTxt(Base);

	if (founded_by_name != "Error")
		replaceLugs(Base, founded_by_name);	//çàìåíà 
	convertToTxt(Base);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
