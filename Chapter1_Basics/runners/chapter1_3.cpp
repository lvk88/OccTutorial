//OpenCASCADE tutorials
//Laszlo Kudela
//November 2015

#include "Chapter1_Basics/inc/PointOnCurveDistributor.hpp"
#include "Chapter1_Basics/inc/WriteCoordinatesToFile.hpp"
#include "Chapter1_Basics/inc/AreaCalculations.hpp"
#include "Utilities/inc/constants.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	//Create a circle like before
	gp_Pnt centerPoint(2.5,2.5,0);
	gp_Dir normalDirection(0.0,0.0,1.0);
	gp_Dir xDirection(1.0,0.0,0.0);
	gp_Ax2 axis(centerPoint,normalDirection,xDirection);

	//Creating the circle
	gp_Circ circle(axis,2.5);

	Standard_Integer resolution = 20;

	//Here, an array of gp_Pnt is allocated, with 500 elements
	//Note that the indexing runs from 1 to 500, instead of the
	//standard convention of 0-499
	TColgp_Array1OfPnt pointsOnCircle(1,resolution);

	//Distribute the points and write them out to a file
	PointOnCurveDistribution::distributePointsOnCurve(circle,pointsOnCircle,0.0,2.0*PI,resolution);
	WriteCoordinatesToFile::writeCoordinatesToFile("chapter3points.txt",pointsOnCircle);

	//Sum the area of the small triangles, to get an approximate area
	//The for loop builds triangles with two corners on the circumference
	//and the center of the circle as third point
	double totalArea = 0.0;
	for(Standard_Integer i=1;i<=resolution;i++)
	{
		gp_Pnt firstPntOfTriangle = pointsOnCircle.Value(i);
		gp_Pnt secondPntOfTriangle;
		if(i != resolution)
		{
			secondPntOfTriangle = pointsOnCircle.Value(i+1);
		}
		else
		{
			//If we are at the end of the array, take the first point
			//because of periodicity
			secondPntOfTriangle = pointsOnCircle.Value(1);
		}
		gp_Pnt thirdPntOfTriangle = centerPoint;
		//A Handle (like a smart pointer) is built to an array of points
		Handle_TColgp_HArray1OfPnt trianglePointsArray = new TColgp_HArray1OfPnt(1,3);
		trianglePointsArray->ChangeValue(1) = firstPntOfTriangle;
		trianglePointsArray->ChangeValue(2) = secondPntOfTriangle;
		trianglePointsArray->ChangeValue(3) = thirdPntOfTriangle;
		totalArea += AreaCalculations::calculateTriangleArea(trianglePointsArray);
		
	}
	std::cout << "Polygonized area: " << totalArea << std::endl;
	std::cout << "Reference area: " << circle.Area() << std::endl;
	std::cout << "Error " << fabs(totalArea-circle.Area())/circle.Area() << std::endl;

	return 0;
}
