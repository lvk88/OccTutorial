//OpenCASCADE tutorials by Laszlo Kudela
//2015 November
//Chapter 1.2 Basics

#include <iostream>
#include <fstream>

#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax2.hxx>
#include <gp_Circ.hxx>
#include <ElCLib.hxx>

#include "Utilities/inc/constants.hpp"

int main(int argc, char *argv[])
{
	//We create a circle centered at (2.5,2.5) with a radius of 2.5	
	//A circle needs to know
	//its center (2.5,2.5)
	//its orientation (lies on the xy plane, i.e. its normal is the z axis)
	//its radius (2.5)
	
	gp_Pnt centerPoint(2.5,2.5,0);
	gp_Dir normalDirection(0.0,0.0,1.0);
	gp_Dir xDirection(1.0,0.0,0.0);
	gp_Ax2 axis(centerPoint,normalDirection,xDirection);

	//Creating the circle
	gp_Circ circle(axis,2.5);

	//Some convenience functions provided by the circle class
	std::cout << "Circle area is: " << circle.Area() << std::endl;
	std::cout << "Circle circumference is: " << circle.Length() << std::endl;

	//Create a scaled copy of the circle
	gp_Circ circle2 = circle.Scaled(gp_Pnt(2.5,2.5,0.0),2.0);		
	std::cout << "Scaled circle area is: " << circle2.Area() << std::endl;
	std::cout << "Scaled circle circumference is: " << circle2.Length() << std::endl;

	//Evaluating geometric entities happens through the ElClib package
	//ElClib = Elementary Curve operations
	//We now evaluate 15 points on the circle and write the resulting coordinates into a file
  	
	//Divide the interval into 100 points
 	Standard_Integer numberOfSamplePoints = 20;
	double deltaU = 2*PI/(numberOfSamplePoints - 1);

	std::ofstream file;
	file.open("chapter1_2_circlePoints.txt");

	for(Standard_Integer i = 0; i<numberOfSamplePoints;i++)
	{
		gp_Pnt pointOnCircle = ElCLib::Value(i*deltaU,circle);	
		file << pointOnCircle.X() << " " << pointOnCircle.Y() << " " << pointOnCircle.Z() << " " << std::endl; 
	}
	file.close();

	file.open("chapter1_2_circleTangents.txt");
	//We can evaluate the tangent vector by using the D1 function from ElClib
	for(Standard_Integer i=0;i<numberOfSamplePoints;i++)
	{
		gp_Pnt pointOnCircle;
		gp_Vec tangentVector;
		ElCLib::D1(i*deltaU,circle2,pointOnCircle,tangentVector);
		file << pointOnCircle.X() << " " << pointOnCircle.Y() << " " << pointOnCircle.Z() << " " << tangentVector.X() << " " << tangentVector.Y() 
			<< " " << tangentVector.Z() << std::endl;
	}
	file.close();

	//Exercise: create an ellipse from the gp package, evaluate 25 points on its circumference together
	//with the local NORMAL vectors that are pointing outwards. Note: to get the normal vector, simply rotate 
	//the tangent by 90 degrees clockwise
			
	return 0;
}
