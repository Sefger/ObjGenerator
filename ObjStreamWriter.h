#pragma once  

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class Vertex {
private:
    double x;
    double y;
    double z;
public:
    Vertex(double _x, double _y, double _z);
    double getX();
    double getY();
    double getZ();
};

class ObjStreamWriter {
private:
    std::ofstream& filePath;  // Ссылка на поток
    std::vector<Vertex> vec;
public:
    int size;
    int getSize();
    ObjStreamWriter(std::ofstream& filePath);  // Принимает ссылку
    void addVertex(double x, double y, double z);
    void addLine(int vertexIndexStart, int vertexIndexEnd);
    void addFacet(int vertexIndex1, int vertexIndex2, int vertexIndex3);
};