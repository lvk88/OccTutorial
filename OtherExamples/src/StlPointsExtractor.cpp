//OpenCASCADE tutorials by Laszlo Kudela
//December 2015
//
#include "../inc/StlPointsExtractor.hpp"

#include "TopoDS.hxx"
#include "TopoDS_Vertex.hxx"
#include "TColgp_HArray1OfPnt.hxx"
#include "TopExp.hxx"
#include "TopTools_IndexedMapOfShape.hxx"

#include "BRep_Tool.hxx"

StlPointsExtractor::StlPointsExtractor()
{

}
StlPointsExtractor::~StlPointsExtractor()
{

}
Handle_TColgp_HArray1OfPnt StlPointsExtractor::extractVerticesFromTopoDSShape(const TopoDS_Shape& shape)
{
	TopTools_IndexedMapOfShape vertices;
	TopExp::MapShapes(shape,TopAbs_VERTEX,vertices);

	Handle_TColgp_HArray1OfPnt result = new TColgp_HArray1OfPnt(1,vertices.Extent());

	for(Standard_Integer i = 1;i<=vertices.Extent();i++)
	{
		TopoDS_Vertex vertex = TopoDS::Vertex(vertices.FindKey(i));
		gp_Pnt currentGeometricPoint = BRep_Tool::Pnt(vertex);
		result->SetValue(i,currentGeometricPoint);
	}

	return result;

}
