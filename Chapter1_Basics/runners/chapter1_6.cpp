//OpenCASCADE tutorial by Laszlo Kudela
//November 2015

#include "BSplCLib.hxx"

#include "TColgp_Array1OfPnt.hxx"
#include "TColStd_Array1OfReal.hxx"
#include "TColStd_Array1OfInteger.hxx"

int main(int argc, char *argv[])
{
	//This example will demonstrate how to use BSplClib to perform elementary
	//computations on B-Spline curves. As we know from the theory of B-Splines,
	//they are defined by a polynomial degree, a set of controls points (denoted as poles in OpenCASCADE)
	//and a knot vector. We will create a 2nd order B-Spline with three poles.
	//This means that the number of knots required is
	//
	//m = n+p+1
	//m = 3+2+1 = 6 -> we need 6 knots to define the spline
	//
	//If the curve has to cross the first and the last control points
	//the multiplicity of the knots have to be p+1 = 3.
	//Thus, we have two knots, one at the beginning of the parameter space,
	//the other on at the end. Both of them has a multiplicity 3.
	//We begin by defining the knot vector, an array with two elements
 	TColStd_Array1OfReal knots(1,2);	
	knots.ChangeValue(1) = 0.0;
	knots.ChangeValue(2) = 1.0;

	//We then define the multiplicity of the knots, both of them is 3
	TColStd_Array1OfInteger multiplicites(1,2);
	multiplicites.SetValue(1,3);
	multiplicites.SetValue(2,3);

	//Now, we need a set of control points. OpenCASCADE denotes them as poles.
	TColgp_Array1OfPnt controlPoints(1,3);
	controlPoints.SetValue(1,gp_Pnt(1.0,0.0,0.0));
	controlPoints.SetValue(2,gp_Pnt(1.0,1.0,0.0));
	controlPoints.SetValue(3,gp_Pnt(0.0,1.0,0.0));
	
	//We also have to assign a "weight" to each control point, in case
	//the curve is a NURBS. Here, we have a simple B-Spline, so no need
	//for special weights.
	TColStd_Array1OfReal weights(1,3);
	weights.SetValue(1,1.0);
	weights.SetValue(2,1.0);
	weights.SetValue(3,1.0);

	//The result of the evaluation will be stored in evalPoint
	gp_Pnt evalPoint;

	//Let's evaluate the first point on the curve
	BSplCLib::D0(0.0,0,2,Standard_False,controlPoints,weights,knots,multiplicites,evalPoint);
	std::cout << evalPoint.X() << " " << evalPoint.Y() << " " << evalPoint.Z() << std::endl;

	BSplCLib::D0(0.5,0,2,Standard_False,controlPoints,weights,knots,multiplicites,evalPoint);
	std::cout << evalPoint.X() << " " << evalPoint.Y() << " " << evalPoint.Z() << std::endl;

	BSplCLib::D0(1.0,0,2,Standard_False,controlPoints,weights,knots,multiplicites,evalPoint);
	std::cout << evalPoint.X() << " " << evalPoint.Y() << " " << evalPoint.Z() << std::endl;

 	//To evaluate the tangent, we can call the D1 function (first derivative)
	//The derivative should be (0,2,0) at parameter u=0, and (-2,0,0) at u=1
	gp_Vec tangentVector;
	BSplCLib::D1(0.0,0,2,Standard_False,controlPoints,weights,knots,multiplicites,evalPoint,tangentVector);
	std::cout << "Tangent at u=0 " <<  tangentVector.X() << " " << tangentVector.Y() << " " << tangentVector.Z() << std::endl;

	BSplCLib::D1(1.0,0,2,Standard_False,controlPoints,weights,knots,multiplicites,evalPoint,tangentVector);
	std::cout << "Tangent at u=1 " <<  tangentVector.X() << " " << tangentVector.Y() << " " << tangentVector.Z() << std::endl;

	//Let's evaluate 10 points on the curve with their tangents, and save them into a file
	//You can display this file using the python script included in the tutorials, as follows:
	
	//python plotVectors.yp bSpline.txt
	//This will create a "vectors.png" file that you can open with any image viewer
	
	std::ofstream file;
	file.open("bSpline.txt");
	double deltaU = 1.0 / 10.0;
	for (int i = 0; i <= 10; ++i) {
		BSplCLib::D1(i*deltaU,0,2,Standard_False,controlPoints,weights,knots,multiplicites,evalPoint,tangentVector);
		file << evalPoint.X() << " " <<evalPoint.Y() << " " <<evalPoint.Z() << " " << tangentVector.X() << " " << tangentVector.Y() << " " 
			<< tangentVector.Z() <<  std::endl;
	}


	return 0;

}
