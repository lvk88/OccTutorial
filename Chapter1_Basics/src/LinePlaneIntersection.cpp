//OpenCASCADE Tutorials
//Laszlo Kudela
//Nov 19, 2015

#include <Chapter1_Basics/inc/LinePlaneIntersection.hpp>

#include "math_FunctionWithDerivative.hxx"
#include "math_FunctionRoot.hxx"
#include "math_DirectPolynomialRoots.hxx"
#include "ElCLib.hxx"

LinePlaneIntersection::LinePlaneIntersection() {
	// TODO Auto-generated constructor stub

}

LinePlaneIntersection::~LinePlaneIntersection() {
	// TODO Auto-generated destructor stub
}

LinePlaneIntersection::LinePlaneIntersectionSolution LinePlaneIntersection::intersectLineWithPlane(const gp_Lin& line,
		const gp_Pln& plane) {

	Standard_Real A,B,C,D;
	plane.Coefficients(A,B,C,D);

	gp_Pnt lineBasePoint = line.Location();
	gp_Dir lineDirection = line.Direction();

	Standard_Real X = A*lineDirection.X()+B*lineDirection.Y()+C*lineDirection.Z();
	Standard_Real Y = A*lineBasePoint.X()+lineBasePoint.Y()+lineBasePoint.Z()+D;

	math_DirectPolynomialRoots rootFinder(X,Y);
	rootFinder.Dump(std::cout);

	LinePlaneIntersectionSolution result;

	if(rootFinder.InfiniteRoots())
	{
		result.state = LinePlaneIntersectionSolution::InfiniteSolutions;
	}
	else if(rootFinder.NbSolutions() == 0)
	{
		result.state = LinePlaneIntersectionSolution::NoSolution;
	}
	else
	{
		result.state = LinePlaneIntersectionSolution::OneSolution;
		result.intersectionPoint = ElCLib::Value(rootFinder.Value(1),line);
	}

	return result;

}
