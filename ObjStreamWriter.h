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
    std::vector<Vertex> vecVertex;
  
public:
    int getLastVertexIndex();
    ObjStreamWriter(std::ofstream& filePath);  // Принимает ссылку
    int addVertex(double x, double y, double z);
    void addLine(int vertexIndexStart, int vertexIndexEnd);
    void addFacet(int vertexIndex1, int vertexIndex2, int vertexIndex3);
    void addNamedObject(std::string text);
};