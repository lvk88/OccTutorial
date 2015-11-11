#include <iostream>
#include <iomanip>
#include "BRepPrimAPI_MakeCylinder.hxx"
#include "BRepPrimAPI_MakeBox.hxx"
#include "BRepAlgoAPI_Cut.hxx"
#include "STEPControl_Writer.hxx"
#include "BRepGProp.hxx"
#include "GProp_GProps.hxx"


int main(int argc, char *argv[])
{
        std::cout << "------- OpenCASCADE Tutorial by Laszlo Kudela -------" << std::endl;	
        std::cout << "------- Chapter 0: Demonstrative example      -------" << std::endl;	

	//Create a simple box with a size 100x100x50
	gp_Pnt lowerLeftCornerOfBox(-50.0,-50.0,0.0);
 	BRepPrimAPI_MakeBox boxMaker(lowerLeftCornerOfBox,100,100,50);
	TopoDS_Shape box = boxMaker.Shape();
	
	//Create a cylinder with a radius 25.0 and height 50.0 
 	BRepPrimAPI_MakeCylinder cylinderMaker(25.0,50.0);
	TopoDS_Shape cylinder = cylinderMaker.Shape();

	//Cut the cylinder out from the box
	BRepAlgoAPI_Cut cutMaker(box,cylinder);
	TopoDS_Shape boxWithHole = cutMaker.Shape();
	
	//Write it to a file
	STEPControl_Writer writer;
	writer.Transfer(boxWithHole,STEPControl_AsIs);
	writer.Write("boxWithHole.stp");

 	std::cout << "Created box with hole, file is written to boxWithHole.stp" << std::endl;	

        GProp_GProps volumeProperties;
	BRepGProp::VolumeProperties(boxWithHole,volumeProperties);

	std::cout << std::setprecision(14) << "Mass of the model is: " << volumeProperties.Mass() << std::endl;
	std::cout << "Center of mass is: " << volumeProperties.CentreOfMass().X() << " " << volumeProperties.CentreOfMass().Y() << " " << volumeProperties.CentreOfMass().Z() << std::endl;
	

	return 0;
}
