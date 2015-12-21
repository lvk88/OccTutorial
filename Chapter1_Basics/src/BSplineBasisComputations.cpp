//OpenCASCADE tutorial by Laszlo Kudela
//December 2015

#include "../inc/BSplineBasisComputations.hpp"

#include "TColStd_HArray1OfReal.hxx"
#include "BSplCLib.hxx"

BSplineBasisComputations::BSplineBasisComputations()
{

}
BSplineBasisComputations::~BSplineBasisComputations()
{

}

void BSplineBasisComputations::calculateBasisFunctions(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree, 
				Standard_Real parameter, math_Matrix& basisFunctions)
{
	Standard_Integer numberOfNonVanishingFunctions = degree + 1;
	Standard_Integer firstNonZeroBSplineIndex;
	
	math_Matrix condensedBasisFunctions(1,1,1,numberOfNonVanishingFunctions);
	
	BSplCLib::EvalBsplineBasis(1,0,degree+1,knots->Array1(),parameter,firstNonZeroBSplineIndex,condensedBasisFunctions);

//	std::cout << "Parameter " << parameter <<  " first non-zero basis " << firstNonZeroBSplineIndex << std::endl;
//	std::cout << "Condensed functions: " << condensedBasisFunctions <<   std::endl;

	for(Standard_Integer i = 0;i<numberOfNonVanishingFunctions;i++)
	{
		basisFunctions(1,firstNonZeroBSplineIndex + i) = condensedBasisFunctions(1,i+1);
	}

	return;
}


void BSplineBasisComputations::calculatePeriodicBasisFunctions(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree, Standard_Real parameter, math_Matrix& basisFunctions)
{
	Standard_Integer numberOfNonVanishingFunctions = degree + 1;
	Standard_Integer firstNonZeroBSplineIndex;
	Standard_Integer knotIndex;
	Standard_Real newParameter;

	//Get valid range of the spline
	Standard_Real firstValidKnotIndex = knots->Lower() + degree;
	Standard_Real lastValidKnotIndex = knots->Upper() - degree;

	std::cout << "Valid knot indices: " << firstValidKnotIndex << " " << lastValidKnotIndex << std::endl;

	//Map the parameter in the valid range
	BSplCLib::LocateParameter(degree,knots->Array1(),parameter,true,firstValidKnotIndex,lastValidKnotIndex,knotIndex,newParameter);
	
	//Evaluate basis at the valid parameter
	BSplineBasisComputations::calculateBasisFunctions(knots,degree,newParameter,basisFunctions);	

	std::cout << "Calculated basis functions at " << newParameter << std::endl;
	std::cout << basisFunctions << std::endl;

	math_Matrix newBasisFunctions(basisFunctions);
	newBasisFunctions.Init(0.0);
	//We have to copy the periodic values in the correct range
	if(parameter < knots->Value(firstValidKnotIndex))
	{
		//Copy values of the last n functions to the first n
		for(Standard_Integer n=1;n<=degree;n++)
		{
			newBasisFunctions(1,n) = basisFunctions(1,basisFunctions.UpperCol()-degree + n);					
		}
	basisFunctions = newBasisFunctions;
	}
	else if(parameter > knots->Value(lastValidKnotIndex))
	{
		//Copy values of the last n functions to the first n
		for(Standard_Integer n=1;n<=degree;n++)
		{
			 newBasisFunctions(1,basisFunctions.UpperCol()-degree+n) = basisFunctions(1,n);
		}
	basisFunctions = newBasisFunctions;
	}



	return;	
}

double BSplineBasisComputations::evaluateBasisFunction(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree,
	       			Standard_Real parameter, Standard_Integer basisFunctionIndex)
{
	Standard_Integer totalNumberOfBasisFunctions = knots->Length() - 1 - degree;
	math_Matrix basisFunctions(1,1,1,totalNumberOfBasisFunctions);
	basisFunctions.Init(0.0);

	BSplineBasisComputations::calculateBasisFunctions(knots,degree,parameter,basisFunctions);

	return basisFunctions(1,basisFunctionIndex + 1);
}

double BSplineBasisComputations::evaluatePeriodicBSplineBasisFunction(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree, Standard_Real parameter, Standard_Integer basisFunctionIndex)
{
	Standard_Integer totalNumberOfBasisFunctions = knots->Length() - 1 - degree;
	math_Matrix basisFunctions(1,1,1,totalNumberOfBasisFunctions);
	basisFunctions.Init(0.0);

	BSplineBasisComputations::calculatePeriodicBasisFunctions(knots,degree,parameter,basisFunctions);
	std::cout << "Basis at parameter " << parameter << std::endl;
	std::cout << basisFunctions  << std::endl;

	return basisFunctions(1,basisFunctionIndex + 1);
}
