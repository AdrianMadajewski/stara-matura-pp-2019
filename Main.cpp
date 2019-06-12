#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using uint = unsigned int;
using vec = std::vector<std::string>;
using std::string;

vec loadData(const string filename)
{
	vec loaded{};
	std::ifstream data;
	data.open(filename);

	if (!data.is_open())
	{
		std::cout << "Cannot open file " + filename + '\n';
		return loaded;
	}

	string readen;
	while (!data.eof())
	{
		std::getline(data, readen);
		loaded.push_back(readen);
	}
	data.close();
	return loaded;
}

int charToInt(const char c) { return c - '0'; }

bool isWoman(const string pesel)
{
	size_t len{ pesel.length() };
	return charToInt(pesel[len - 2]) % 2 == 0;
}

bool below2000(const string pesel) { return pesel[0] != '0'; }

bool fromNovember(const string pesel)
{
	if (below2000(pesel))
	{
		return pesel[2] == '1' && pesel[3] == '1';
	}
	else
	{
		return pesel[2] == '3' && pesel[3] == '1';
	}
}

bool isValid(const string pesel)
{
	size_t len		{ pesel.length() };
	uint value		{ 0 };
	uint temp		{};

	std::vector<int> multipliers{ 1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1 };
	for (uint i = 0; i < multipliers.size(); ++i)
	{
		temp = charToInt(pesel[i]);
		value += temp * multipliers[i];
	}

	return value % 10 == 0;
}

int main()
{
	vec data				{ loadData("dane.txt") };
	uint men				{ 0 };
	uint women				{ 0 };
	uint bornInNovember			{ 0 };
	vec invalid				{};

	for (auto pesel : data)
	{
		if (isWoman(pesel)) women++;
		else men++;

		if (fromNovember(pesel)) bornInNovember++;

		if (!isValid(pesel)) invalid.push_back(pesel);
	}
	
	std::cout << "6.1\n";
	std::cout << "women: " << women << '\n';
	std::cout << "men: " << men << '\n';
	std::cout << "6.2\n";
	std::cout << "born in November: " << bornInNovember << '\n';
	std::cout << "6.3\n";
	for (auto pesel : invalid)
		std::cout << "invalid: " + pesel + '\n';

	return 0;
}
