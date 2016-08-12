//OpenCASCADE tutorials by Laszlo Kudela
//2015 November
//Chapter 1.4 Least squares fitting
#include "../inc/LeastSquaresFitting.hpp"

#include "TColgp_HArray1OfPnt.hxx"
#include "math_MultipleVarFunctionWithGradient.hxx"
#include "math_Vector.hxx"
#include "math_BFGS.hxx"

#include <cmath>
#include <iostream>

class CircleFitCostFunction : public math_MultipleVarFunctionWithGradient
{
public:
	CircleFitCostFunction(Handle_TColgp_HArray1OfPnt pointsToFitOnto);
	virtual ~CircleFitCostFunction();

	Standard_Integer NbVariables() const;
	Standard_Boolean Value(const math_Vector& X, Standard_Real& F);
	Standard_Boolean Gradient(const math_Vector& X, math_Vector& G);
	Standard_Boolean Values(const math_Vector& X, Standard_Real& F, math_Vector& G);
	


private:
	Handle_TColgp_HArray1OfPnt myPointsToFitOnto;
	
};

CircleFitCostFunction::CircleFitCostFunction(Handle_TColgp_HArray1OfPnt pointsToFitOnto) : myPointsToFitOnto(pointsToFitOnto)
{
}

CircleFitCostFunction::~CircleFitCostFunction()
{
}

Standard_Integer CircleFitCostFunction::NbVariables() const
{
	return 3;
}
Standard_Boolean CircleFitCostFunction::Value(const math_Vector& X, Standard_Real& F)
{
	double sum = 0.0;
	for(Standard_Integer i = myPointsToFitOnto->Lower();i<=myPointsToFitOnto->Upper();i++)
	{
		double pxMinusCx = myPointsToFitOnto->Value(i).X()-X(1);
		double pyMinusCy = myPointsToFitOnto->Value(i).Y()-X(2);
                sum += (pxMinusCx*pxMinusCx+pyMinusCy*pyMinusCy-X(3)*X(3))*(pxMinusCx*pxMinusCx+pyMinusCy*pyMinusCy-X(3)*X(3));
	}
 	
	F = sum;

	return Standard_True;
}
Standard_Boolean CircleFitCostFunction::Gradient(const math_Vector& X, math_Vector& G)
{
	double g0 = 0.0;
	double g1 = 0.0;
	double g2 = 0.0;
	
	for(Standard_Integer i = myPointsToFitOnto->Lower();i<=myPointsToFitOnto->Upper();i++)
	{
		double pxMinusCx = myPointsToFitOnto->Value(i).X()-X(1);
		double pyMinusCy = myPointsToFitOnto->Value(i).Y()-X(2);
                double distance = pxMinusCx*pxMinusCx+pyMinusCy*pyMinusCy-X(3)*X(3);
                g0 += pxMinusCx*distance;
                g1 += pyMinusCy*distance;
                g2 += distance;
	}

	G(1) = -4.0*g0;
	G(2) = -4.0*g1;
	G(3) = -4.0*X(3)*g2;

	return Standard_True;

}
Standard_Boolean CircleFitCostFunction::Values(const math_Vector& X, Standard_Real& F, math_Vector& G)
{
	this->Value(X,F);
	this->Gradient(X,G);
	return Standard_True;
}

LeastSquaresFitting::LeastSquaresFitting ()
{
}
LeastSquaresFitting::~LeastSquaresFitting ()
{
}

gp_Circ LeastSquaresFitting::fitLeastSquaresCircleToPoints(const Handle_TColgp_HArray1OfPnt& points)
{
	//Get initial guess for least squares fit
	InitialGuessForLeastSquaresFitting initialGuess = findInitialGuess(points);

	math_Vector startingPointForBFGS(1,3);
	startingPointForBFGS(1) = initialGuess.myCenterPoint.X();
	startingPointForBFGS(2) = initialGuess.myCenterPoint.Y();
	startingPointForBFGS(3) = initialGuess.myRadius;

	CircleFitCostFunction costFunction(points);

	math_BFGS minimizer(costFunction,startingPointForBFGS);

	math_Vector minimum(1,3);

	if (minimizer.IsDone()) 
	{
		std::cout << "Minimizer is done, result is:" << std::endl;
		minimizer.Location(minimum);
		std::cout << minimum(1) << " " << minimum(2) << " " << minimum(3) << std::endl;
		
	} else 
	{
		std::cout << "Error: minimizer failed!" << std::endl;		
	}

	gp_Ax2 axis = gp::XOY();
	axis.SetLocation(gp_Pnt(minimum(1),minimum(2),0.0));
	gp_Circ result(axis,minimum(3));

	return result;

}

LeastSquaresFitting::InitialGuessForLeastSquaresFitting LeastSquaresFitting::findInitialGuess(const Handle_TColgp_HArray1OfPnt& points)
{
	//Compute center of gravity for point set
	double cx=0.0;
	double cy=0.0;

	for(Standard_Integer i=points->Lower();i<=points->Upper();i++)
	{
		cx += points->Value(i).X();
		cy += points->Value(i).Y();
	}

	cx /= points->Length();
	cy /= points->Length();

	gp_Pnt centerPoint(cx,cy,0.0);

	//Compute average radius
	double averageRadius = 0.0;
	for(Standard_Integer i=points->Lower();i<=points->Upper();i++)
	{
		averageRadius += centerPoint.Distance(points->Value(i));
	}
	averageRadius /= points->Length();

	return InitialGuessForLeastSquaresFitting(centerPoint,averageRadius);
}
