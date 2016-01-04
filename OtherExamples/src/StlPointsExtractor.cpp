//OpenCASCADE tutorials by Laszlo Kudela
//December 2015
//
#include "../inc/StlPointsExtractor.hpp"
#include "TopTools_ListIteratorOfListOfShape.hxx"
#include "TopoDS_Builder.hxx"
#include "TopoDS_Compound.hxx"
#include "TopoDS_Edge.hxx"
#include "TopExp_Explorer.hxx"
#include "TopTools_IndexedDataMapOfShapeListOfShape.hxx"
#include "TopTools_ListOfShape.hxx"

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

TopoDS_Shape StlPointsExtractor::extractManifoldBoundaries(const TopoDS_Shape& shape)
{
	//For every edge in the triangulation, we pick those that have only one parent face
	//We will store the resulting edges in boundaryEdges
	TopTools_ListOfShape boundaryEdges;
	TopExp_Explorer explorer;

	TopTools_IndexedDataMapOfShapeListOfShape mapOfEdges;
	TopExp::MapShapesAndAncestors(shape,TopAbs_EDGE,TopAbs_FACE,mapOfEdges);
	std::cout << mapOfEdges.Extent() << " edges found in STL file"  << std::endl;
	
	std::cout << "Extracting manifold edges " << std::endl;
	for(explorer.Init(shape,TopAbs_EDGE,TopAbs_SHAPE);explorer.More();explorer.Next())
	{
		TopoDS_Edge currentEdge = TopoDS::Edge(explorer.Current());		
		const TopTools_ListOfShape& parentsOfCurrentEdge = mapOfEdges.FindFromKey(currentEdge);
		if(parentsOfCurrentEdge.Extent() == 1)
		{
			boundaryEdges.Append(currentEdge);
		}
	}

	std::cout << "Found " << boundaryEdges.Extent() << " boundary edges." << std::endl;

	TopoDS_Compound collectorOfEdges;
	TopoDS_Builder builder;
	builder.MakeCompound(collectorOfEdges);
	
	for(TopTools_ListIteratorOfListOfShape it( boundaryEdges  );it.More();it.Next())
	{
		builder.Add(collectorOfEdges,it.Value());
	}

	return collectorOfEdges;
	
}
