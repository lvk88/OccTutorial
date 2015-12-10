//OpenCASCADE Tutorials by Laszlo Kudela
//December 2015

#include "../inc/BSplineSurfaceContainer.hpp"



BSplineSurfaceContainer::BSplineSurfaceContainer(
		Handle_TColgp_HArray2OfPnt controlPoints,
		Handle_TColStd_HArray2OfReal weights,
		Handle_TColStd_HArray1OfReal uKnots,
		Handle_TColStd_HArray1OfReal vKnots,
		Handle_TColStd_HArray1OfInteger uMultiplicities,
		Handle_TColStd_HArray1OfInteger vMultiplicities,
		Standard_Integer uDegree,
		Standard_Integer vDegree
		) 
{
	myControlPoints = controlPoints;
	myWeights = weights;
	myUKnots = uKnots;
	myVKnots = vKnots;
	myUMultiplicities = uMultiplicities;
	myVMultiplicities = vMultiplicities;
	myUDegree = uDegree;
	myVDegree = vDegree;
	return;
}

BSplineSurfaceContainer::~BSplineSurfaceContainer()
{

}


IMPLEMENT_STANDARD_HANDLE(BSplineSurfaceContainer,Standard_Transient)
IMPLEMENT_STANDARD_RTTIEXT(BSplineSurfaceContainer,Standard_Transient)	

