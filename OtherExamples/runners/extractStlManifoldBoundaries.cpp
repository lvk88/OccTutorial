//OpenCASCADE tutorial by Laszlo Kudela
//December 2015

#include "../inc/CreateCurvedPlateWithHole.hpp"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Edge.hxx"
#include "TopExp_Explorer.hxx"
#include "TopExp.hxx"
#include "TopoDS.hxx"
#include "TopoDS_Builder.hxx"
#include "TopTools_SequenceOfShape.hxx"
#include "TopTools_ListOfShape.hxx"
#include "TopTools_ListIteratorOfListOfShape.hxx"
#include "TopTools_IndexedDataMapOfShapeListOfShape.hxx"

#include "BRep_Tool.hxx"

#include "StlAPI.hxx"

#include "STEPControl_Writer.hxx"

int main(int argc, char *argv[])
{
	//Create a curved plate with hole
	std::cout << "Creating plate with hole... ";
	TopoDS_Shape plateWithHoleShape = CreateCurvedPlateWithHole::createCurvedPlateWithHole();
	std::cout << "done" << std::endl;

	//Make a triangulation out of it, write to STL
	TopoDS_Face plateWithHoleFace;
	TopExp_Explorer explorer;
	for(explorer.Init(plateWithHoleShape,TopAbs_FACE,TopAbs_SHAPE);explorer.More();explorer.Next())
	{
		plateWithHoleFace = TopoDS::Face(explorer.Current());
	}
	std::cout << "Writing STL... " << std::flush;
	StlAPI::Write(plateWithHoleFace,"curvedPlateWithHole.stl",true);
	std::cout << "done" << std::endl;


	//Read STL, extract boundary edges of STL mesh
	std::cout << "Reading STL..." << std::flush;
	TopoDS_Shape stlShape;
	StlAPI::Read(stlShape,"curvedPlateWithHole.stl");
	std::cout << "done" << std::endl;

	//For every edge in the triangulation, we pick those that have only one parent face
	//We will store the resulting edges in boundaryEdges
	
	TopTools_ListOfShape boundaryEdges;

	TopTools_IndexedDataMapOfShapeListOfShape mapOfEdges;
	TopExp::MapShapesAndAncestors(stlShape,TopAbs_EDGE,TopAbs_FACE,mapOfEdges);
	std::cout << mapOfEdges.Extent() << " edges found in STL file"  << std::endl;
	
	std::cout << "Extracting manifold edges " << std::endl;
	for(explorer.Init(stlShape,TopAbs_EDGE,TopAbs_SHAPE);explorer.More();explorer.Next())
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

	//Write the result in STEP file
	STEPControl_Writer writer;
	writer.Transfer(collectorOfEdges,STEPControl_AsIs);
	writer.Write("curvePlateWithHoleEdges.stp");



	
	return 0;
}
