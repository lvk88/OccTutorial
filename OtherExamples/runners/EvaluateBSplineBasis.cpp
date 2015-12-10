//OpenCASCADE Tutorials by Laszlo Kudela
//December 2015

#include "Chapter1_Basics/inc/CylinderToBspline.hpp"
#include "Chapter1_Basics/inc/BSplineSurfaceContainer.hpp"

#include "math_Matrix.hxx"
#include "BSplCLib.hxx"
#include "TColStd_HArray1OfInteger.hxx"
#include "TColStd_HArray1OfReal.hxx"

#include <iostream>

int main(int argc, char *argv[])
{
	gp_Cylinder cylinder(gp_Ax3(gp::XOY()),50);

	Handle_BSplineSurfaceContainer surfaceContainer = CylinderToBSpline::convertClosedCylinderToBSpline(cylinder,50.0);

	TColStd_Array1OfInteger orderArray(1,1);
	orderArray.SetValue(1,0);

	//Flatten knot vector
	Standard_Integer knotSequenceLength = BSplCLib::KnotSequenceLength(surfaceContainer->myUMultiplicities->Array1(),surfaceContainer->myUDegree,true);

	std::cout << "Knot sequence length: " << knotSequenceLength << std::endl;

	TColStd_Array1OfReal flatKnots(1,knotSequenceLength);

	BSplCLib::KnotSequence(surfaceContainer->myUKnots->Array1(),surfaceContainer->myUMultiplicities->Array1(),2,true,flatKnots);
	for(Standard_Integer i=1;i<=flatKnots.Length();i++)
	{
		std::cout << flatKnots.Value(i) << std::endl;
	}

	TColStd_Array1OfReal parameters(1,1);
	parameters.SetValue(1,1.0);

	math_Matrix bSplineMatrix(1,1,1,5);
	bSplineMatrix.Init(0.0);
	Standard_Integer upperBandwidth, lowerBandwidth;

	Standard_Integer result;
	try
	{
	result = BSplCLib::BuildBSpMatrix(parameters,orderArray,flatKnots,2,bSplineMatrix,upperBandwidth,lowerBandwidth);
	}catch(Standard_RangeError& e)
	{
		e.Print(std::cout);
	}

	std::cout << result << std::endl;

	if(!result)
	{
		bSplineMatrix.Dump(std::cout);
	}

	//Standard_Integer FirstNonZeroIndex;

	//Standard_Real delta = (2./3. - 1./3.) / 20.;
	//for(size_t i=0;i<=20;i++)
	//{
	//	Standard_Real parameter = 1./3. + i * delta;
	//	BSplCLib::EvalBsplineBasis(-1,0,3,flatKnots,parameter,FirstNonZeroIndex,bSplineMatrix);
	//	std::cout << "Parameter: " << parameter << std::endl;
	//	bSplineMatrix.Dump(std::cout);
	//	std::cout << "With first non zero index at: " << FirstNonZeroIndex << std::endl;
	//}

	
	return 0;
}
