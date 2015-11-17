#ifndef LEASTSQUARESFITTING_HPP
#define LEASTSQUARESFITTING_HPP 
//OpenCASCADE tutorials by Laszlo Kudela
//2015 November
//Chapter 1.3 Least squares fitting

class Handle_TColgp_HArray1OfPnt;

#include "gp_Circ.hxx"

class LeastSquaresFitting
{
public:
	LeastSquaresFitting ();
	virtual ~LeastSquaresFitting ();

	static gp_Circ fitLeastSquaresCircleToPoints(const Handle_TColgp_HArray1OfPnt& points);

private:
	struct InitialGuessForLeastSquaresFitting
	{
		InitialGuessForLeastSquaresFitting(gp_Pnt center, double radius)
		{
			myCenterPoint = center;
			myRadius = radius;
		}
		gp_Pnt myCenterPoint;
		double myRadius;
	};

	static InitialGuessForLeastSquaresFitting findInitialGuess(const Handle_TColgp_HArray1OfPnt& points);	

};

#endif
