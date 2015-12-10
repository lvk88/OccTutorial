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

	for(Standard_Integer i = 0;i<numberOfNonVanishingFunctions;i++)
	{
		basisFunctions(1,firstNonZeroBSplineIndex + i) = condensedBasisFunctions(1,i+1);
	}

	return;
}
double BSplineBasisComputations::evaluateBasisFunction(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree,
	       			Standard_Real parameter, Standard_Integer basisFunctionIndex)
{
	Standard_Integer totalNumberOfBasisFunctions = knots->Length() - 1 - degree;
	math_Matrix basisFunctions(1,1,1,totalNumberOfBasisFunctions);

	BSplineBasisComputations::calculateBasisFunctions(knots,degree,parameter,basisFunctions);

	return basisFunctions(1,basisFunctionIndex + 1);
}
