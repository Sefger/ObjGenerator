#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include <sstream>
#include <algorithm>
//using namespace std;
//надо записать счётчик, который сможет генирировать всегда, потому что иначе будет f 1 2 3
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
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    double getZ() {
        return z;
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

bool isNumber(const std::string& s) {
    return !s.empty() && std::find_if_not(s.begin(),
        s.end(), [](char c) { return std::isdigit(c) || c == '.'; }) == s.end();
}
//может стоит убрать эту функцию
bool checkIsDouble(std::string str) {
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
//можно будет сделать чтобы generatePolygon использовал generateTriangle, и так далее
// методы для генерации
void generateTriangle(std::ofstream& myFile, std::vector<Vertex> vec) {
    for (Vertex v : vec) {
        myFile << "v " << v.getX() << " " << v.getY() << " " << v.getZ();
    }
    myFile << "f" << " 1" << " 2" << " 3" << std::endl;
}
void generateTriangle(std::ofstream& myFile, double x, double y, double z) {
    myFile << "v " << x << " " << y << " " << z;
    myFile << "f" << " 1" << " 2" << " 3" << std::endl;
}
void generatePolygon(std::ofstream& myFile, double length, double width) {
    myFile << "v " << 0.0 << " " << 0.0 << " " << 0.0 << std::endl;
    myFile << "v " << length << " " << 0.0 << " " << 0.0 << std::endl;
    myFile << "v " << length << " " << width << " " << 0.0 << std::endl;
    myFile << "v " << 0.0 << " " << width << " " << 0.0 << std::endl;
    myFile << "f 1 2 3" << std::endl;
    myFile << "f 1 3 4" << std::endl;
};
void generateParallelepiped(std::ofstream& myFile, double length, double width, double height) {

    myFile << "v " << 0.0 << " " << 0.0 << " " << 0.0 << std::endl;
    myFile << "v " << length << " " << 0.0 << " " << 0.0 << std::endl;
    myFile << "v " << length << " " << width << " " << 0.0 << std::endl;
    myFile << "v " << 0.0 << " " << width << " " << 0.0 << std::endl;
    myFile << "v " << 0.0 << " " << 0.0 << " " << height << std::endl;
    myFile << "v " << length << " " << 0.0 << " " << height << std::endl;
    myFile << "v " << length << " " << width << " " << height << std::endl;
    myFile << "v " << 0.0 << " " << width << " " << height << std::endl;

    myFile << "f 1 2 3" << std::endl;
    myFile << "f 1 3 4" << std::endl;
    // Верхняя грань
    myFile << "f 5 6 7" << std::endl;
    myFile << "f 5 7 8" << std::endl;
    // Передняя грань
    myFile << "f 1 5 6" << std::endl;
    myFile << "f 1 6 2" << std::endl;
    // Задняя грань
    myFile << "f 3 7 8" << std::endl;
    myFile << "f 3 8 4" << std::endl;
    // Левая грань
    myFile << "f 1 5 8" << std::endl;
    myFile << "f 1 8 4" << std::endl;
    // Правая грань
    myFile << "f 2 6 7" << std::endl;
    myFile << "f 2 7 3" << std::endl;

}
//разговоры с пользователем
void createPolygon(std::ofstream& myFile) {
    std::cout << "Length and width: ";
    std::string length;
    std::string width;
    std::cin >> length;
    std::cin >> width;
    if (checkIsDouble(length) && checkIsDouble(width)) {
        generatePolygon(myFile, std::stod(length), std::stod(width));
    }
}
void createParallelepiped(std::ofstream& myFile) {
    std::cout << "Length, width and height";
    std::string length;
    std::string width;
    std::string height;
    std::cin >> length;
    std::cin >> width;
    std::cin >> height;
    if (checkIsDouble(height) && checkIsDouble(length) && checkIsDouble(width)) {
        generateParallelepiped(myFile, std::stod(length), std::stod(width), std::stod(height));
    }
}

void createTriangle(std::ofstream& myFile) {
    int count = 0;
    std::string str1;
    std::string str2;
    std::string str3;
    std::vector<Vertex> v;
    double x;
    double y;
    double z;
    while (count < 3) {
        std::cout << "Input cord (x, y, z):";
        std::cin >> str1;
        std::cin >> str2;
        std::cin >> str3;
        std::vector<Vertex> temp;

        if (checkIsDouble(str1) && checkIsDouble(str2) && checkIsDouble(str3)) {
            x = std::stod(str1);
            y = std::stod(str1);
            z = std::stod(str1);
            //здесь вроде должен быть new, но компилятор жаловался
            temp.push_back(Vertex(x, y, z));
            myFile << "v" << " " << str1 << " " << str2 << " " << str3 << std::endl;
            count++;
        }
        generateTriangle(myFile, temp);
    }

}



int main() {

    std::ofstream myFile("obj1.obj");

    // Запись в файл  
    std::cout << "What model you want to generate?\n"
        "\n1 - triangle"
        "\n2 - polygon"
        "\n3 - parallelepiped"
        "\n5 - pyramid"
        "\n6 - cube" << std::endl;
    int num;

    std::cin >> num;

    switch (num)
    {
    case 1:
        createTriangle(myFile);
        break;

    case 2:
        createPolygon(myFile);
        break;

    case 3:
        createParallelepiped(myFile);
        break;

    case 4:
        break;
    case 5:
        break;
    }
    myFile.close();
}