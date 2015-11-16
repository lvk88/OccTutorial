//OpenCASCADE tutorials
//Laszlo Kudela
//November 2015

#include "Standard_Integer.hxx"
#include "TColgp_Array1OfPnt.hxx"
#include "ElCLib.hxx"

namespace PointOnCurveDistribution
{
template<typename CurveType>
void DistributePointsOnCurve(const CurveType& curve, TColgp_Array1OfPnt& pointArray, double lowerLimit, double upperLimit, Standard_Integer resolution)
{
	double deltaU = (upperLimit - lowerLimit) / (resolution - 1);
	for(Standard_Integer i = 0;i<resolution;i++)
	{
		gp_Pnt pointOnCurve = ElCLib::Value(i*deltaU,curve);
		pointArray.SetValue(i+1,pointOnCurve);
	}
}
}
