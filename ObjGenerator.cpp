#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include <sstream>
#include <algorithm>
//using namespace std;

class Vertex {
private:
	double x;
	double y;
	double z;
public:
	Vertex(double _x, double _y, double _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	Vertex(std::string str) {

	}

};
std::vector<std::string> split(const std::string& str) {
	std::istringstream stream(str);
	std::vector<std::string> tokens;
	std::string word;

	while (stream >> word) {
		tokens.push_back(word);
	}

	return tokens;
}

// Функция для проверки, что строка состоит только из цифр и точек
bool is_number(const std::string& s) {
	return !s.empty() && std::find_if_not(s.begin(),
		s.end(), [](char c) { return std::isdigit(c) || c == '.'; }) == s.end();
}

// Основная функция для преобразования строки в вектор чисел double
std::vector<double> string_to_double_vector(const std::string& input) {
	std::vector<std::string> words = split(input); // Разбиваем строку на слова
	std::vector<double> result;

	for (const auto& word : words) {
		if (!is_number(word)) {
			throw std::runtime_error("Некорректный ввод: строка содержит нечисловые данные.");
		}
		result.push_back(std::stod(word));
	}

	return result;
}
bool check_is_double(std::string str) {
	try
	{
		double value = std::stod(str);
		return true;
	}
	catch (const std::invalid_argument&)
	{
		std::cerr << "No conversion could be performed" << std::endl;
		return false;
	}
	catch (const std::out_of_range&)
	{
		std::cerr << "Could not convert string to double, value falls out of range" << std::endl;
		return false;
	}
}
int main() {

	std::ofstream MyFile("obj1.obj");

	// Запись в файл	
	std::cout << "What model you want to generate?\n"
		"\n1 - triangle"
		"\n2 - parallelepiped"
		"\n3 - polygon"
		"\n4 - pyramid"
		"\n5 - cube" << std::endl;
	int num;

	std::cin >> num;
	int count = 0;
	std::string str1;
	std::string str2;
	std::string str3;
	std::vector<Vertex> v;
	double x;
	double y;
	double z;
	switch (num)
	{
	case 1:
		while (count < 3) {
			std::cout << "Input cord (x, y, z):";
			std::cin >> str1;
			std::cin >> str2;
			std::cin >> str3;
			std::vector<double> temp;

			if (check_is_double(str1) && check_is_double(str2) && check_is_double(str3)) {
				MyFile << "v" << " " << str1 << " " << str2 << " " << str3 << std::endl;
				count++;
			}
		}
		MyFile << "f" << " 1" << " 2" << " 3" << std::endl;
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;
	case 5:
		break;
	}
	MyFile.close();
}