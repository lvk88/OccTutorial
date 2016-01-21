//OpenCASADE tutorial by Laszlo Kudela
//January 2016

#include "BRepTools_ReShape.hxx"
#include "BRepTools.hxx"
#include "TopTools.hxx"
#include "STEPControl_Writer.hxx"
#include "Utilities/inc/constants.hpp"

#include "BRepBuilderAPI_Transform.hxx"
#include "gp_Trsf.hxx"
#include "TopoDS.hxx"
#include "TopoDS_Solid.hxx"
#include "TopExp.hxx"
#include "TopTools_IndexedMapOfShape.hxx"
#include "TopExp_Explorer.hxx"
#include "TopoDS_Compound.hxx"
#include "STEPControl_Reader.hxx"

#include <iostream>

int main(int argc, char *argv[])
{
	//In this tutorial, we read in a STEP file containing to solids
	//and modify the underlying solids in some way
	
	//The first argument of the program is the name of the STEP file
	
	if(argc < 2)
	{
		std::cout << "Usage: moveAndRotate InputFile" << std::endl;
		std::cout << "InputFile: a file in STP format" << std::endl;
		return 1;
	}
	
	//First, we read in a STEP file
	STEPControl_Reader reader;
	reader.ReadFile(argv[1]);

	std::cout << reader.TransferRoots() << " roots transferred." << std::endl;

	//The shape that was read in is stored in a single TopoDS_Shape
	//If this is an assembly file, the shape should be a compound
	TopoDS_Shape shape = reader.OneShape();

	if(shape.ShapeType() != TopAbs_COMPOUND)
	{
		std::cout << "Error: the read shape is not a compound!" << std::endl;
		return 1;
	}
	
	//Next, we extract the first two solids that compose the compound shape
	//To this end, we have to "explore" the compound shape and find the solids
	//contained in it
	TopTools_IndexedMapOfShape mapOfShapes;
	TopExp::MapShapes(shape,TopAbs_SOLID,mapOfShapes);
	std::cout << mapOfShapes.Extent() << " solids found in STEP file." << std::endl;

	TopoDS_Solid firstSolid = TopoDS::Solid(mapOfShapes.FindKey(1));
	TopoDS_Solid secondSolid = TopoDS::Solid(mapOfShapes.FindKey(2));

	//We are going to move the second solid along the z axis in the negative direction
	//This needs a gp_Trsf object
	gp_Trsf translation;
	translation.SetTranslation(gp_Pnt(0.0,0.0,0.0),gp_Pnt(0.0,0.0,-50.0));

	//Perform the translation
	BRepBuilderAPI_Transform translationTransformer(translation);
	translationTransformer.Perform(secondSolid,false);
	TopoDS_Solid solidAfterTranslation = TopoDS::Solid(translationTransformer.ModifiedShape(secondSolid));

	//Next we rotate the first solid around the y axis by 45 degrees
	gp_Trsf rotation;
	rotation.SetRotation(gp::OY(),1.0 * PI / 4.0);
	BRepBuilderAPI_Transform rotationTransformer(rotation);
	rotationTransformer.Perform(solidAfterTranslation);
	TopoDS_Solid solidAfterRotation = TopoDS::Solid(rotationTransformer.ModifiedShape(solidAfterTranslation));

	//Next, we replace the original shape in the compound by the new, rotated and transformed shape
	BRepTools_ReShape reShaper;
	reShaper.Replace(secondSolid,solidAfterRotation);
	shape = reShaper.Apply(shape);


	//Now we store the resulting solids in another STEP file
	STEPControl_Writer writer;
	writer.Transfer(shape,STEPControl_AsIs);
	writer.Write("moveAndRotate_output.stp");

	return 0;
}
