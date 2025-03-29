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
        myFile << "v " << v.getX() << " " << v.getY() << " " << v.getZ()<<"\n";
    }
    myFile << "f" << " 1" << " 2" << " 3\n" << std::endl;
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
void generateCube(std::ofstream& myFile, double side) {
    generateParallelepiped(myFile, side, side, side);
}
void generatePiramid(std::ofstream& myFile, double length, double width, double height) {
    // ширина по x 
    // длина по y
    //пока пирамида имеет квадратное основание
    myFile << "v " << 0.0 << " " << 0.0 << " " << 0.0 << std::endl;
    myFile << "v " << 0.0 << " " <<  length << " " << 0.0 << std::endl;
    myFile << "v " << width << " " << 0.0 << " " << 0.0 << std::endl;
    myFile << "v " << width << " " << length << " " << 0.0 << std::endl;
    myFile << "v " << width/2 << " " << length/2 << " " << height << std::endl;
    //основания
    myFile << "f 1 2 3 "<<std::endl;
    myFile << "f 2 3 4 "<<std::endl;
    //стороны
    myFile << "f 1 2 5"<<std::endl;
    myFile << "f 2 4 5"<<std::endl;
    myFile << "f 3 4 5"<<std::endl;
    myFile << "f 1 3 5"<<std::endl;
}
void generateTruncatedPiramid(std::ofstream& myFile, double length, double width, double height, double newHeight) {
    if (newHeight >= height) {
        std::cout << "Invalid input";
        return;
    }
    

    // Рассчитываем параметры усечения
    double ratio = newHeight / height;
    double topWidth = width * ratio;
    double topLength = length * ratio;

    // Координаты вершин (ось Z - вертикальная)
    // Нижнее основание (z = 0)
    double v1x = -width / 2, v1y = -length / 2, v1z = 0.0;  // 1
    double v2x = width / 2, v2y = -length / 2, v2z = 0.0;  // 2
    double v3x = width / 2, v3y = length / 2, v3z = 0.0;  // 3
    double v4x = -width / 2, v4y = length / 2, v4z = 0.0;  // 4

    // Верхнее основание (z = newHeight)
    double v5x = -topWidth / 2, v5y = -topLength / 2, v5z = newHeight;  // 5
    double v6x = topWidth / 2, v6y = -topLength / 2, v6z = newHeight;  // 6
    double v7x = topWidth / 2, v7y = topLength / 2, v7z = newHeight;  // 7
    double v8x = -topWidth / 2, v8y = topLength / 2, v8z = newHeight;  // 8

    // Записываем вершины
   

    // Нижнее основание
    myFile << "v " << v1x << " " << v1y << " " << v1z << "\n";
    myFile << "v " << v2x << " " << v2y << " " << v2z << "\n";
    myFile << "v " << v3x << " " << v3y << " " << v3z << "\n";
    myFile << "v " << v4x << " " << v4y << " " << v4z << "\n";

    // Верхнее основание
    myFile << "v " << v5x << " " << v5y << " " << v5z << "\n";
    myFile << "v " << v6x << " " << v6y << " " << v6z << "\n";
    myFile << "v " << v7x << " " << v7y << " " << v7z << "\n";
    myFile << "v " << v8x << " " << v8y << " " << v8z << "\n";

    // Грани (все треугольники)


    // Нижнее основание (2 треугольника)
    myFile << "f 1 2 3\n";
    myFile << "f 1 3 4\n";

    // Верхнее основание (2 треугольника)
    myFile << "f 5 7 6\n";
    myFile << "f 5 8 7\n";

    // Боковые грани (8 треугольников)
    myFile << "f 1 2 6\n";  // Передняя сторона 1
    myFile << "f 1 6 5\n";  // Передняя сторона 2
    myFile << "f 2 3 7\n";  // Правая сторона 1
    myFile << "f 2 7 6\n";  // Правая сторона 2
    myFile << "f 3 4 8\n";  // Задняя сторона 1
    myFile << "f 3 8 7\n";  // Задняя сторона 2
    myFile << "f 4 1 5\n";  // Левая сторона 1
    myFile << "f 4 5 8\n";

}
//разговоры с пользователем
void createPolygon(std::ofstream& myFile) {
    std::cout << "Length and width: ";
    std::string sLength, sWidth;

    std::cin >> sLength;
    std::cin >> sWidth;
    if (checkIsDouble(sLength) && checkIsDouble(sWidth)) {
        generatePolygon(myFile, std::stod(sLength), std::stod(sWidth));
    }
}
void createParallelepiped(std::ofstream& myFile) {
    std::cout << "Length, width and height: ";
    std::string sLength, sWidth, sHeight;
    std::cin >> sLength;
    std::cin >> sWidth;
    std::cin >> sHeight;
    if (checkIsDouble(sHeight) && checkIsDouble(sLength) && checkIsDouble(sWidth)) {
        generateParallelepiped(myFile, std::stod(sLength), std::stod(sWidth), std::stod(sHeight));
    }
}

void createTriangle(std::ofstream& myFile) {
    int count = 0;
    std::string str1, str2, str3;
    std::vector<Vertex> v;
    double x, y, z;
    std::vector<Vertex> temp;
    while (count < 3) {
        std::cout << "Input cord (x, y, z):";
        std::cin >> str1;
        std::cin >> str2;
        std::cin >> str3;
        

        if (checkIsDouble(str1) && checkIsDouble(str2) && checkIsDouble(str3)) {
            x = std::stod(str1);
            y = std::stod(str1);
            z = std::stod(str1);
            //здесь вроде должен быть new, но компилятор жаловался
            temp.push_back(Vertex(x, y, z));
            count++;
        }
        
    }
    generateTriangle(myFile, temp);

}

void createCube(std::ofstream& myFile) {
    std::cout << "Input side: ";
    std::string side;
    std::cin >> side;
    if (checkIsDouble(side)) {
        generateCube(myFile, std::stod(side));
    }
}
void createPiramid(std::ofstream& myFile) {
    std::cout << "Input length, width, height: ";
    std::string sLength, sWidth, sHeight;
    std::cin >> sLength;
    std::cin >> sWidth;
    std::cin >> sHeight;
    if (checkIsDouble(sLength) && checkIsDouble(sWidth) && checkIsDouble(sHeight)) {
        generatePiramid(myFile, std::stod(sLength), std::stod(sWidth), std::stod(sHeight));
    }
}
void createTruncatedPiramid(std::ofstream& myFile) {
    std::cout << "Input length, width, height, new height: ";
    std::string sLength, sWidth, sHeight, sNewHeight;
    std::cin >> sLength;
    std::cin >> sWidth;
    std::cin >> sHeight;
    std::cin >> sNewHeight;
    if (checkIsDouble(sLength) && checkIsDouble(sWidth) && checkIsDouble(sHeight)&&checkIsDouble(sNewHeight)) {
        generateTruncatedPiramid(myFile, std::stod(sLength), std::stod(sWidth), std::stod(sHeight), std::stod(sNewHeight));
    }
}
int main() {

    std::ofstream myFile("obj2.obj");

    //// Запись в файл  
    //std::cout << "What model you want to generate?\n"
    //    "\n1 - triangle"
    //    "\n2 - polygon"
    //    "\n3 - parallelepiped"
    //    "\n4 - pyramid"
    //    "\n5 - cube" 
    //"\n6 - truncated piramid\n";
    //int num;

    //std::cin >> num;

    //switch (num)
    //{
    //case 1:
    //    //работает
    //    createTriangle(myFile);
    //    break;

    //case 2:
    //    //работает
    //    createPolygon(myFile);
    //    break;

    //case 3:
    //    //работает
    //    createParallelepiped(myFile);
    //    break;

    //case 4:
    //    // работает
    //    createPiramid(myFile);
    //    break;
    //case 5:
    //    createCube(myFile);
    //    break;

    //case 6:
    //    createTruncatedPiramid(myFile);
    //    break;
    //}
    generateTruncatedPiramid(myFile, 10, 10, 10, 4);
    myFile.close();
}