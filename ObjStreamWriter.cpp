#include "ObjStreamWriter.h"  

// –еализаци€ методов класса Vertex
Vertex::Vertex(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

double Vertex::getX() { return x; }
double Vertex::getY() { return y; }
double Vertex::getZ() { return z; }

//  онструктор теперь принимает ссылку и инициализирует ее в списке инициализации
ObjStreamWriter::ObjStreamWriter(std::ofstream& filePath) : filePath(filePath) {
}

int ObjStreamWriter::addVertex(double x, double y, double z) {
    Vertex v(x, y, z);
    filePath << "v " << x << " " << y << " " << z << std::endl;
    vecVertex.push_back(v);
    return vecVertex.size();
}

void ObjStreamWriter::addLine(int vertexIndexStart, int vertexIndexEnd) {
    filePath << "l " << vertexIndexStart << " " << vertexIndexEnd << std::endl;
  
}

void ObjStreamWriter::addFacet(int vertexIndex1, int vertexIndex2, int vertexIndex3) {
    filePath << "f " << vertexIndex1 << " " << vertexIndex2 << " " << vertexIndex3 << std::endl;
}
int ObjStreamWriter::getLastVertexIndex() { return vecVertex.size(); };