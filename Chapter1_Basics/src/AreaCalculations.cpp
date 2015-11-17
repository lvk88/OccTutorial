//OpenCASCADE tutorials
//Laszlo Kudela
//November 2015

#include "Chapter1_Basics/inc/AreaCalculations.hpp"
#include "math_Matrix.hxx"

namespace AreaCalculations
{
double calculateTriangleArea(const Handle_TColgp_HArray1OfPnt triangleCorners)
{
	//We compute the area of the triangle using the determinant approach
	//First, allocate a 3 by 3 matrix for the calculation
	math_Matrix matrixForAreaCalculation(0,2,0,2);

	//Then fill it with the coordinates of the triangle corners
	matrixForAreaCalculation(0,0) = triangleCorners->Value(1).X();
	matrixForAreaCalculation(0,1) = triangleCorners->Value(1).Y();
	matrixForAreaCalculation(0,2) = 1.0;
	matrixForAreaCalculation(1,0) = triangleCorners->Value(2).X();
	matrixForAreaCalculation(1,1) = triangleCorners->Value(2).Y();
	matrixForAreaCalculation(1,2) = 1.0;
	matrixForAreaCalculation(2,0) = triangleCorners->Value(3).X();
	matrixForAreaCalculation(2,1) = triangleCorners->Value(3).Y();
	matrixForAreaCalculation(2,2) = 1.0;

	double area = 0.5 * matrixForAreaCalculation.Determinant();
	return area;
}
}
