#include "Chapter1_Basics/inc/LeastSquaresFitting.hpp"
#include "Chapter1_Basics/inc/PointOnCurveDistributor.hpp"
#include "Chapter1_Basics/inc/WriteCoordinatesToFile.hpp"
#include "Utilities/inc/constants.hpp"

#include "TColgp_HArray1OfPnt.hxx"

#include <cstdlib>
#include <ctime>


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

	//Seed random generator
	std::srand(static_cast<unsigned>(time(0)));

	//Distribute the points and write them out to a file
	PointOnCurveDistribution::distributePointsOnCurve(circle,pointsOnCircle,0.0,2.0*PI,resolution);
	Handle_TColgp_HArray1OfPnt pointsForLeastSquaresFit = new TColgp_HArray1OfPnt(1,resolution);
	for (Standard_Integer i = 1; i <= pointsForLeastSquaresFit->Upper(); ++i) 
	{
		double randomXShift = static_cast<double>(rand())/(static_cast<double>(RAND_MAX/0.5));
		double randomYShift = static_cast<double>(rand())/(static_cast<double>(RAND_MAX/0.5));
		pointsForLeastSquaresFit->ChangeValue(i) = pointsOnCircle.Value(i);		
		pointsForLeastSquaresFit->ChangeValue(i).SetX(pointsForLeastSquaresFit->ChangeValue(i).X()+randomXShift);		
		pointsForLeastSquaresFit->ChangeValue(i).SetY(pointsForLeastSquaresFit->ChangeValue(i).Y()+randomYShift);		
		
	}
	WriteCoordinatesToFile::writeCoordinatesToFile("chapter4.txt",pointsForLeastSquaresFit->Array1());

	gp_Circ fittedCircle = LeastSquaresFitting::fitLeastSquaresCircleToPoints(pointsForLeastSquaresFit);

	PointOnCurveDistribution::distributePointsOnCurve(fittedCircle,pointsOnCircle,0.0,2.0*PI,resolution);
	WriteCoordinatesToFile::writeCoordinatesToFile("chapter4_fittedpoints.txt",pointsOnCircle);


	
	return 0;
}
