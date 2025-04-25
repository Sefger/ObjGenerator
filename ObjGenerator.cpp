#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "ObjStreamWriter.h"
//using namespace std;
//надо записать счётчик, который сможет генирировать всегда, потому что иначе будет f 1 2 3

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

void generateTriangle(std::ofstream& file, std::vector<Vertex> vec) {
    ObjStreamWriter writer(file);
    
    for (Vertex v : vec) {
        
        writer.addVertex(v.getX(), v.getY(), v.getZ());
    }
    
    writer.addFacet(writer.getSize(), writer.getSize() - 1, writer.getSize() - 2);
}
void generateTriangle(std::ofstream& file, double x, double y, double z) {
    ObjStreamWriter writer(file);
    writer.addVertex(x, y, z);
    writer.addFacet(writer.getSize() , writer.getSize() - 1, writer.getSize() - 2);
   
}
void generatePolygon(std::ofstream& file, double length, double width) {
    ObjStreamWriter writer(file);
    writer.addVertex(0, 0, 0);//-4
    writer.addVertex(length, 0, 0);//-3
    writer.addVertex(length, width, 0);//-2
    writer.addVertex(0, width, 0);//-1
    writer.addFacet(writer.getSize() - 3, writer.getSize() - 2, writer.getSize() - 1);
    writer.addFacet(writer.getSize() - 3, writer.getSize() - 1, writer.getSize());
};
void generateParallelepiped(std::ofstream& file, double length, double width, double height) {
    ObjStreamWriter writer(file);
    writer.addVertex(0, 0, 0);
    writer.addVertex(length, 0, 0);
    writer.addVertex(length, width, 0);
    writer.addVertex(0, width, 0);
    writer.addVertex(0, 0, height);

    writer.addVertex(length, 0, height);
    writer.addVertex(length, width, height);
    writer.addVertex(0, width, height);
  

    writer.addFacet(writer.getSize() - 7, writer.getSize() - 6, writer.getSize() - 5);
    writer.addFacet(writer.getSize() - 7, writer.getSize() - 5, writer.getSize() - 4);
 

    writer.addFacet(writer.getSize() - 3, writer.getSize() - 2, writer.getSize()-1);
    writer.addFacet(writer.getSize() - 3, writer.getSize() - 1, writer.getSize());

    
    
    writer.addFacet(writer.getSize() - 7, writer.getSize() - 3, writer.getSize() - 2);
  
    writer.addFacet(writer.getSize() - 7, writer.getSize() - 2, writer.getSize()-6);


    writer.addFacet(writer.getSize() - 5, writer.getSize() - 1, writer.getSize());
    writer.addFacet(writer.getSize() - 5, writer.getSize(), writer.getSize() - 4);
   
    writer.addFacet(writer.getSize() - 7, writer.getSize() - 3, writer.getSize());
    writer.addFacet(writer.getSize() - 7, writer.getSize(), writer.getSize() - 4);
  

    writer.addFacet(writer.getSize() - 6, writer.getSize() - 2, writer.getSize() - 1);
    writer.addFacet(writer.getSize() - 6, writer.getSize() - 1, writer.getSize() - 5);
    

}
void generateCube(std::ofstream& myFile, double side) {
    generateParallelepiped(myFile, side, side, side);
}
void generatePiramid(std::ofstream& file, double length, double width, double height) {
    // ширина по x 
    // длина по y
    //пока пирамида имеет квадратное основание
    ObjStreamWriter writer(file);
    writer.addVertex(0, 0, 0);// 1 - 5
    writer.addVertex(0, length, 0);// 2 - 4
    writer.addVertex(width, 0, 0);// 3 - 3
    writer.addVertex(width, length, 0);// 4 - 2
    writer.addVertex(width / 2, length / 2, height);// 5 - 1

    

    writer.addFacet(writer.getSize() - 4, writer.getSize() - 3, writer.getSize() - 2);
    writer.addFacet(writer.getSize() - 3, writer.getSize() - 2, writer.getSize() - 1);
    
    ////стороны
    writer.addFacet(writer.getSize() - 4, writer.getSize() - 3, writer.getSize());
    writer.addFacet(writer.getSize() - 3, writer.getSize() - 1, writer.getSize());
   
    writer.addFacet(writer.getSize() - 2, writer.getSize() - 1, writer.getSize() );
    writer.addFacet(writer.getSize() - 4, writer.getSize() -2, writer.getSize() );

}
void generateTruncatedPiramid(std::ofstream& file, double length, double width, double height, double newHeight) {
    if (newHeight >= height) {
        std::cout << "Invalid input";
        return;
    }
    ObjStreamWriter writer(file);

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
    writer.addVertex(v1x, v1y, v1z);
    writer.addVertex(v2x, v2y, v2z);
    writer.addVertex(v3x, v3y, v3z);
    writer.addVertex(v4x, v4y, v4z);

    writer.addVertex(v5x, v5y, v5z);
    writer.addVertex(v6x, v6y, v6z);
    writer.addVertex(v7x, v7y, v7z);
    writer.addVertex(v8x, v8y, v8z);
    


    // Нижнее основание (2 треугольника)
    writer.addFacet(writer.getSize() - 7, writer.getSize() - 6, writer.getSize() - 5);
    writer.addFacet(writer.getSize() - 7, writer.getSize() - 5, writer.getSize() - 4);


    // Верхнее основание (2 треугольника)
    writer.addFacet(writer.getSize() - 3, writer.getSize() - 1, writer.getSize() - 2);
    writer.addFacet(writer.getSize()-3, writer.getSize(), writer.getSize()-1);
   /* myFile << "f 5 7 6\n";
    myFile << "f 5 8 7\n";*/

    // Боковые грани (8 треугольников)
    writer.addFacet(writer.getSize() - 7, writer.getSize() - 6, writer.getSize() - 2);
    writer.addFacet(writer.getSize() - 7, writer.getSize() - 2, writer.getSize() - 3);
   

    writer.addFacet(writer.getSize() - 6, writer.getSize() - 5, writer.getSize() - 1);
    writer.addFacet(writer.getSize() - 6, writer.getSize() - 1, writer.getSize() - 2);
  

    writer.addFacet(writer.getSize() - 5, writer.getSize() - 4, writer.getSize());

    writer.addFacet(writer.getSize() - 5, writer.getSize() , writer.getSize() - 1);



    writer.addFacet(writer.getSize() - 4, writer.getSize() - 7, writer.getSize() - 3);
    writer.addFacet(writer.getSize() - 4, writer.getSize() - 3, writer.getSize());
 

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
            y = std::stod(str2);
            z = std::stod(str3);
           
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
    std::cout << "What model you want to generate?\n"
        "\n1 - triangle"
        "\n2 - polygon"
        "\n3 - parallelepiped"
        "\n4 - pyramid"
        "\n5 - cube" 
    "\n6 - truncated piramid\n";
    int num;

    std::cin >> num;

    switch (num)
    {
    case 1:
        //тестировал
        createTriangle(myFile);
        break;

    case 2:
        //тестировал
        createPolygon(myFile);
        break;

    case 3:
        //тестировал
        createParallelepiped(myFile);
        break;

    case 4:
        // тестировал
        createPiramid(myFile);
        break;
    case 5:
        // тестировал
        createCube(myFile);
        break;

    case 6:
        //тестировал
        createTruncatedPiramid(myFile);
        break;
    }

    myFile.close();
}
