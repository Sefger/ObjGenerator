#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <STEPControl_Writer.hxx>
#include <StlAPI_Writer.hxx>
#include <VrmlAPI_Writer.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <Poly_Triangulation.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include "ObjStreamWriter.h"
#include <fstream>
void exportShapeToObj(ObjStreamWriter& objWriter, const TopoDS_Shape& shape, const std::string& objectName) {
    objWriter.addNamedObject(objectName);

    for (TopExp_Explorer faceExplorer(shape, TopAbs_FACE); faceExplorer.More(); faceExplorer.Next()) {
        const TopoDS_Face& face = TopoDS::Face(faceExplorer.Current());
        TopLoc_Location location;
        Handle(Poly_Triangulation) triangulation = BRep_Tool::Triangulation(face, location);

        if (!triangulation.IsNull()) {

            const TColgp_Array1OfPnt& nodes = triangulation->MapNodeArray()->Array1();
            int vertexOffset = objWriter.getLastVertexIndex();

            // Записываем вершины
            for (int i = nodes.Lower(); i <= nodes.Upper(); i++) {
                gp_Pnt p = nodes(i).Transformed(location);
                objWriter.addVertex(p.X(), p.Y(), p.Z());
            }

            // Записываем треугольники
            for (int i = 1; i <= triangulation->NbTriangles(); i++) {
                int v1, v2, v3;
                triangulation->Triangle(i).Get(v1, v2, v3);
                // Индексы в OBJ начинаются с 1, а не с 0
                objWriter.addFacet(v1 + vertexOffset,
                    v2 + vertexOffset,
                    v3 + vertexOffset);
            }
        }
    }
}
int main()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(0.0, 40.0, 0.0));

    TopoDS_Shape aTorus = BRepPrimAPI_MakeTorus(anAxis, 5.0, 10.0).Shape();
    BRepMesh_IncrementalMesh(aTorus, 0.1, Standard_True);
   
    // Создаем коробку
    TopoDS_Shape aBox = BRepPrimAPI_MakeBox(3.0, 4.0, 5.0).Shape();

    // Генерируем сетку для коробки
    BRepMesh_IncrementalMesh(aBox, 0.1, Standard_True);

    // Создаем и открываем файл для записи OBJ
    std::ofstream objFile("more-object.obj");
    if (!objFile.is_open()) {
        std::cerr << "Failed to create OBJ file" << std::endl;
        return 1;
    }

    // Создаем писатель OBJ
    ObjStreamWriter objWriter(objFile);

    exportShapeToObj(objWriter, aTorus, "Torus");
    exportShapeToObj(objWriter, aBox, "Box");

    objFile.close();
    return 0;
}
