//OpenCASCADE tutorial by Laszlo Kudela
//December 2015

#include "../inc/CreateCurvedPlateWithHole.hpp"
#include "../inc/StlPointsExtractor.hpp"
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
#include "BRepMesh_IncrementalMesh.hxx"

#include "StlAPI.hxx"

#include "STEPControl_Writer.hxx"

int main(int argc, char *argv[])
{
	//Create a curved plate with hole
	std::cout << "Creating plate with hole... ";
	TopoDS_Shape plateWithHoleShape = CreateCurvedPlateWithHole::createCurvedPlateWithHole();
	std::cout << "done" << std::endl;

	TopoDS_Face plateWithHoleFace;
	TopExp_Explorer explorer;
	//Make a triangulation out of it, write to STL
	for(explorer.Init(plateWithHoleShape,TopAbs_FACE,TopAbs_SHAPE);explorer.More();explorer.Next())
	{
		plateWithHoleFace = TopoDS::Face(explorer.Current());
	}
	std::cout << "Creating mesh..."  << std::flush;
	BRepMesh_IncrementalMesh meshMaker(plateWithHoleFace,0.01,Standard_False);
	std::cout << " done." << std::endl;
	meshMaker.Perform();
	std::cout << "Writing STL... " << std::flush;
	StlAPI::Write(plateWithHoleFace,"curvedPlateWithHole.stl",true);
	std::cout << "done" << std::endl;


	//Read STL, extract boundary edges of STL mesh
	std::cout << "Reading STL..." << std::flush;
	TopoDS_Shape stlShape;
	StlAPI::Read(stlShape,"curvedPlateWithHole.stl");
	std::cout << "done" << std::endl;

	//This function call is the place wehre the actual work is done.
	//Check the source file if you want to know how it works!
	TopoDS_Shape collectorOfEdges = StlPointsExtractor::extractManifoldBoundaries(stlShape);

	//Write the result in STEP file
	STEPControl_Writer writer;
	writer.Transfer(collectorOfEdges,STEPControl_AsIs);
	writer.Write("curvePlateWithHoleEdges.stp");

	return 0;
}
