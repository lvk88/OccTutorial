//OpenCASCADE tutorial by Laszlo Kudela
//January 2016


#include "../inc/TangentMagnitude.hpp"

#include "gp_Vec.hxx"
#include "gp_Pnt.hxx"

TangentMagnitude::TangentMagnitude (Handle_Geom_Curve curve) : myCurve(curve)
{

}
TangentMagnitude::~TangentMagnitude ()
{

}
Standard_Boolean TangentMagnitude::Value(Standard_Real X, Standard_Real& F)
{
	gp_Vec tangentVector;
	gp_Pnt pointLocation;
	
	myCurve->D1(X,pointLocation,tangentVector);

	F = tangentVector.Magnitude();

	return Standard_True;
}
const Handle_Geom_Curve TangentMagnitude::getCurve() const
{
	return myCurve;
}
void TangentMagnitude::setCurve(Handle_Geom_Curve curve)
{
	myCurve = curve;
	return;
}
