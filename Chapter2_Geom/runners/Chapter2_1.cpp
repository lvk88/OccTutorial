//OpenCASCADE tutorial by Laszlo Kudela
//January 2016

//This example demonstrates how to create geometric entities like curves and surfaces from the Geom package
//and apply some transformations on them
//Finally, we compute the length of the curve using the numerical integration provided by OpenCASCADE

#include "Chapter2_Geom/inc/GeometryWriter.hpp"
#include "Chapter2_Geom/inc/TangentMagnitude.hpp"
#include "Utilities/inc/constants.hpp"

#include "TColgp_Array1OfPnt.hxx"
#include "Geom_BezierCurve.hxx"
#include "math_GaussSingleIntegration.hxx"

int main(void)
{

	//Here, a simple Bezier curve is created. It is defined by 4 points in
	//the 3D space, therefore its order will be 3
	
	//A Bezier curve needs a set of control points in its constructor,
	//that we store in a 1D Array of points
	TColgp_Array1OfPnt controlPoints(1,4);

	controlPoints.SetValue(1,gp_Pnt(0.0,0.0,0.0));
	controlPoints.SetValue(2,gp_Pnt(1.0,0.0,1.0/3.0));	
	controlPoints.SetValue(3,gp_Pnt(1.0,1.0,2.0/3.0));	
	controlPoints.SetValue(4,gp_Pnt(1.0,1.0,1.0));	

	Handle_Geom_Curve bezierCurve = new Geom_BezierCurve(controlPoints);

	GeometryWriter::writeGeomEntityToStepFile(bezierCurve,"bezierInitial.stp");

	//Because a Bezier curve inherits from Geom_Geometry, all sorts of geometric transformations can be applied on it
	//Let us rotate the curve around the z axis by 180 degrees
	//Because "Rotate" is a function of the superclass, the function returns a
	//Geom_Geometry object
	Handle_Geom_Geometry rotated = bezierCurve->Rotated(gp::OZ(),PI);

	//If we want to convert it to a curve, we can use the built-in DownCast function of the Handle
	Handle_Geom_Curve rotatedCurve = Handle_Geom_Curve::DownCast(rotated);
	GeometryWriter::writeGeomEntityToStepFile(rotatedCurve,"rotatedBezier.stp");

	//We can also scale the curve, applying a scaling
	Handle_Geom_Curve scaledCurve = Handle_Geom_Curve::DownCast(bezierCurve->Scaled(gp::Origin(),2.0));

	//What are the parametric bounds of the created curve?
	Standard_Real firstParameter = bezierCurve->FirstParameter();
	Standard_Real lastParameter = bezierCurve->LastParameter();

	std::cout << "The parametric bounds of the created curve are: " << firstParameter << " " << lastParameter << std::endl;

	//To evaluate the curve at a given parameter, we can call the function "Value"
	gp_Pnt pointOnCurve = bezierCurve->Value(0.0);
	std::cout << "Point at u = 0.0: " << "(" << pointOnCurve.X() << "," << pointOnCurve.Y() << "," << pointOnCurve.Z() <<")" << std::endl;

	pointOnCurve = bezierCurve->Value(0.5);
	std::cout << "Point at u = 0.5: " << "(" << pointOnCurve.X() << "," << pointOnCurve.Y() << "," << pointOnCurve.Z() <<")" << std::endl;

        pointOnCurve = bezierCurve->Value(1.0);
	std::cout << "Point at u = 1.0: " << "(" << pointOnCurve.X() << "," << pointOnCurve.Y() << "," << pointOnCurve.Z() <<")" << std::endl;

	//To evaluate the tangent vector, we can call the function "D1". For higher derivatives, we have D2,D3,...,DN
	gp_Vec tangentVector;
	bezierCurve->D1(0.0,pointOnCurve,tangentVector);	
	std::cout << "Magnitude of tangent at 0.0: " << tangentVector.Magnitude() << std::endl;
	bezierCurve->D1(0.5,pointOnCurve,tangentVector);	
	std::cout << "Magnitude of tangent at 0.5: " << tangentVector.Magnitude() << std::endl;
	bezierCurve->D1(1.0,pointOnCurve,tangentVector);	
	std::cout << "Magnitude of tangent at 1.0: " << tangentVector.Magnitude() << std::endl;

	//If we integrate the magnitude of the tangent vector along the curve, we get
	//the length. OpenCASCADE provides numerical integration routines to perform this task, called
	//math_GaussSingleIntegration. /All we have to do is to implement a class that inherits
	//from math_Function and implements the function "Value", that for a given X value returns
	//the magnitude of the tangent.
	
        TangentMagnitude functionToBeIntegrated(bezierCurve);	
	math_GaussSingleIntegration integrator(functionToBeIntegrated,firstParameter,lastParameter,5);

	if(integrator.IsDone())
	{
		std::cout << "The length of the curve is approximately " << integrator.Value() << std::endl;
	}

	//Let's compute the length of the rotated and scaled curve
	functionToBeIntegrated.setCurve(rotatedCurve);
	math_GaussSingleIntegration rotatedIntegrator(functionToBeIntegrated,firstParameter,lastParameter,5);
	double rotatedLength = rotatedIntegrator.Value();
	functionToBeIntegrated.setCurve(scaledCurve);
	math_GaussSingleIntegration scaledIntegrator(functionToBeIntegrated,firstParameter,lastParameter,5);
	double scaledLength = scaledIntegrator.Value();

	std::cout << "Length of rotated curve is " << rotatedLength  << std::endl;
	std::cout << "Length of scaled curve is " << scaledLength  << std::endl;

	//If you run this example, you will see that rotation keeps the length of the curve, because
	//it is a rigid transformation, while scaling changes the length.
	
	return 0;
}
