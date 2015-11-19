//OpenCASCADE Tutorials
//Laszlo Kudela
//Nov 19, 2015

#include <Chapter1_Basics/inc/LinePlaneIntersection.hpp>

#include "math_FunctionWithDerivative.hxx"
#include "math_FunctionRoot.hxx"
#include "math_DirectPolynomialRoots.hxx"
#include "ElCLib.hxx"

class LinePlaneIntersectionFunction: public math_FunctionWithDerivative {
public:
	LinePlaneIntersectionFunction(gp_Lin line, gp_Pln plane);

	Standard_Boolean Value(const Standard_Real X, Standard_Real&F);
	Standard_Boolean Derivative(const Standard_Real X, Standard_Real &D);
	Standard_Boolean Values(const Standard_Real X, Standard_Real&F,
			Standard_Real &D);

private:
	gp_Lin myLine;
	gp_Pln myPlane;
};

LinePlaneIntersectionFunction::LinePlaneIntersectionFunction(gp_Lin line,
		gp_Pln plane) :
		myLine(line), myPlane(plane) {
}

Standard_Boolean LinePlaneIntersectionFunction::Value(const Standard_Real X,
		Standard_Real&F) {
	//Get implicit equation of plane
	//A*X + B*Y + C*Z + D = 0
	Standard_Real A, B, C, D;
	myPlane.Coefficients(A, B, C, D);
	gp_Pnt pointOnLine = ElCLib::Value(X, myLine);

	F = (A * pointOnLine.X() + B * pointOnLine.Y() + C * pointOnLine.Z() + D);
	return true;
}
Standard_Boolean LinePlaneIntersectionFunction::Derivative(
		const Standard_Real X, Standard_Real &derivative) {
	Standard_Real A, B, C, D;
	myPlane.Coefficients(A, B, C, D);

	gp_Pnt pointOnLine;
	gp_Vec lineTangent;

	ElCLib::D1(X,myLine,pointOnLine,lineTangent);

	derivative = A*lineTangent.X()+B*lineTangent.Y()+C*lineTangent.Z();

	return true;
}
Standard_Boolean LinePlaneIntersectionFunction::Values(const Standard_Real X,
		Standard_Real&F, Standard_Real &D) {
	this->Value(X,F);
	this->Derivative(X,D);
	return true;
}

LinePlaneIntersection::LinePlaneIntersection() {
	// TODO Auto-generated constructor stub

}

LinePlaneIntersection::~LinePlaneIntersection() {
	// TODO Auto-generated destructor stub
}

gp_Pnt LinePlaneIntersection::intersectLineWithPlane(const gp_Lin& line,
		const gp_Pln& plane) {

//	LinePlaneIntersectionFunction functionToSolve(line,plane);
//
//	Standard_Real firstGuess = 10.0;
//	math_FunctionRoot rootFinder(functionToSolve,firstGuess,1E-10);
//
//	Standard_Real root = rootFinder.Root();
//
//	gp_Pnt result = ElCLib::Value(root,line);

	//Gather the coefficients of the plane
	//Ax+By*Cz*D=0
	Standard_Real A,B,C,D;
	plane.Coefficients(A,B,C,D);

	//Set up equation Ax(u)+B*y(u)+C*z(u)+D=0
	//A(x0+dx*u)+B*(y0+dy*u)+C(z0+dz*u)+D=0
	//u(A*dx+B*dy+C*dz)+(A*x0+B*y0+C*z0+D)=0
	//u*X+Y=0
	gp_Pnt lineBasePoint = line.Location();
	gp_Dir lineDirection = line.Direction();

	Standard_Real X = A*lineDirection.X()+B*lineDirection.Y()+C*lineDirection.Z();
	Standard_Real Y = A*lineBasePoint.X()+lineBasePoint.Y()+lineBasePoint.Z()+D;

	math_DirectPolynomialRoots rootFinder(X,Y);

	Standard_Real root = rootFinder.Value(1);
	gp_Pnt result = ElCLib::Value(root,line);

	return result;

}
