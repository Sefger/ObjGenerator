#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include <sstream>

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
  

};
class ObjStreamWriter {
private:
	std::string filePath;
	std::ofstream fileName;
    std::vector <Vertex> vec;
public:
	ObjStreamWriter(std::string filePath) {
		this->fileName = std::ofstream(filePath);

	}
	void AddVertex(double x, double y, double z) {
        Vertex v = Vertex(x, y, z);
        fileName << "v" << x << " " << y << " " << z << std::endl;
        vec.push_back(v);
	}
	void addLine(int vertexIndexStart, int vertexIndexEnd) {
        fileName << "l" << " " << vertexIndexStart << " " << vertexIndexEnd;
	}
	void addFacet(int vertexIndex1, int vertexIndex2, int vertexIndex3) {
        fileName <<"f" << " " << vertexIndex1 << " " << vertexIndex2 << " " << vertexIndex3 << std::endl;
	}
};
