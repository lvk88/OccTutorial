//OpenCASCADE tutorial by Laszlo Kudela
//December 2015
#ifndef _BSPLINEBASIS_COMPUTATIONS_HPP
#define _BSPLINEBASIS_COMPUTATIONS_HPP 

#include "math_Matrix.hxx"
#include "Standard_Real.hxx"
#include "Standard_Integer.hxx"
#include "Handle_TColStd_HArray1OfReal.hxx"



class BSplineBasisComputations
{
public:
	BSplineBasisComputations ();
	virtual ~BSplineBasisComputations ();

	static void calculateBasisFunctions(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree, Standard_Real parameter, math_Matrix& basisFunctions);
	static void calculatePeriodicBasisFunctions(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree, Standard_Real parameter, math_Matrix& basisFunctions);
	static double evaluateBasisFunction(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree, Standard_Real parameter, Standard_Integer basisFunctionIndex);
	static double evaluatePeriodicBSplineBasisFunction(Handle_TColStd_HArray1OfReal knots, Standard_Integer degree, Standard_Real parameter, Standard_Integer basisFunctionIndex);

private:
	
};

#endif
