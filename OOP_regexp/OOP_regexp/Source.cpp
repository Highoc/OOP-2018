#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>

#include <regex>
#include <string>
#include <map>

#define s string_polynom_without_space

using std::cout;
using std::string;
using std::endl;
using std::fstream;

using std::regex_replace;
using std::regex;

std::map<int, int> polynom;

void printPolynom(fstream& ofstream);
void diffPolynom();
void addPolynomPart(int coefficient, int degree);
void addPolynom(const string& string_polynom);

inline void check(bool cond, string errMsg);

int main()
{
	fstream fsIn("polynomIn.txt", std::ios_base::in);
	fstream fsOut("polynomOut.txt", std::ios_base::out);

	check(fsIn.is_open(), "Не могу открыть файл на чтение");
	check(fsOut.is_open(), "Не могу открыть файл на запись");

	for (string nowLine; getline(fsIn, nowLine);) 
	{
		addPolynom(nowLine);
		diffPolynom();
		printPolynom(fsOut);
	}

	check(!fsIn.bad(), "Какие-то ошибки при работе с файлом");
	check(fsIn.eof(), "Должен был быть достигнут конец файла");
	check(!fsIn.good(), "Невозможно, если до сюда дошли");

	fsIn.close();
	fsOut.close();

	system("pause");
	return 0;
}

void addPolynom(const string& string_polynom)
{
	polynom.clear();

	string string_polynom_without_space = regex_replace(string_polynom, regex("\\s*"), "");

	cout << "> " << string_polynom_without_space << endl;

	if ((string_polynom_without_space[0] != '-') && (string_polynom_without_space[0] != '+'))
	{
		string_polynom_without_space = "+" + string_polynom_without_space;
	}

	string pattern = R"###([-+](((\d+\*)?x(\^\d+)?)|(\d+)))###";
	regex reg_pattern = regex(pattern);

	string now;
	int coef, deg;

	for (auto iter = std::sregex_iterator(s.begin(), s.end(), reg_pattern); iter != std::sregex_iterator(); ++iter)
	{
		coef = 0; deg = 1;
		now = iter->str();

		std::smatch match;
		string patternPart = R"###(([+-]\d*)?\*?(x)?\^?(\d*)?)###";
		std::regex_match(now, match, regex(patternPart));

		if (match[1] == "+")
			coef = 1;
		else if (match[1] == "-")
			coef = -1;
		else
			coef = stoi(match[1]);

		if (match[2] == "")
		{
			deg = 0;
			continue;
		}

		if (match[3] == "")
			deg = 1;
		else
			deg = stoi(match[3]);

		addPolynomPart(coef, deg);
	}
}

void addPolynomPart(int coefficient, int degree)
{
	if (polynom.count(degree) == 0)
	{
		polynom[degree] = coefficient;
	}
	else
	{
		polynom[degree] += coefficient;
	}
}

void printPolynom(fstream& ofstream)
{
	std::ostringstream sstream;
	
	for (auto nowNode = polynom.rbegin(); nowNode != polynom.rend(); nowNode++)
	{
		if (nowNode->second == 0)
		{
			continue;
		}
		sstream << std::showpos << nowNode->second;

		if (nowNode->first == 0)
		{
			continue;
		}
		else if (nowNode->first == 1)
		{
			sstream << "*x";
		}
		else
		{
			sstream << "*x^" << std::noshowpos << nowNode->first;
		}
	}

	string result = "0";
	if (sstream.str() != "")
	{
		result = sstream.str();
	}

	if (result[0] == '+')
	{
		result = result.substr(1);
	}

	cout << "< " << result << endl;
	ofstream << result << endl;
}

void diffPolynom()
{
	for (auto& i : polynom)
	{
		if (i.first == 0)
		{
			i.second = 0;
		}
		else
		{
			polynom[i.first - 1] = i.first * i.second;
			i.second = 0;
		}
	}
}

inline void check(bool cond, string errMsg) {
	if (!cond) {
		std::cerr << errMsg << endl;
		exit(EXIT_FAILURE);
	}
}