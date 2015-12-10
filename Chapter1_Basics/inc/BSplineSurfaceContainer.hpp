//OpenCASCADE tutorials by Laszlo Kudela
//December 2015

#ifndef _BSPLINESURFACECONTAINER_HPP
#define _BSPLINESURFACECONTAINER_HPP 

#include "Handle_TColgp_HArray2OfPnt.hxx"
#include "Handle_TColStd_HArray2OfReal.hxx"
#include "Handle_TColStd_HArray1OfReal.hxx"
#include "Handle_TColStd_HArray1OfInteger.hxx"

#include "Standard_DefineHandle.hxx"
#include "Standard_Transient.hxx"

DEFINE_STANDARD_HANDLE(BSplineSurfaceContainer,Standard_Transient)

class BSplineSurfaceContainer : public Standard_Transient
{
	public:
	BSplineSurfaceContainer(
			Handle_TColgp_HArray2OfPnt controlPoints,
			Handle_TColStd_HArray2OfReal weights,
			Handle_TColStd_HArray1OfReal uKnots,
			Handle_TColStd_HArray1OfReal vKnots,
			Handle_TColStd_HArray1OfInteger uMultiplicities,
			Handle_TColStd_HArray1OfInteger vMultiplicities,
			Standard_Integer uDegree,
			Standard_Integer vDegree
			);

	virtual ~BSplineSurfaceContainer();

	Handle_TColgp_HArray2OfPnt myControlPoints;
	Handle_TColStd_HArray2OfReal myWeights;
	Handle_TColStd_HArray1OfReal myUKnots;
	Handle_TColStd_HArray1OfReal myVKnots;
	Handle_TColStd_HArray1OfInteger myUMultiplicities;
	Handle_TColStd_HArray1OfInteger myVMultiplicities;
	Standard_Integer myUDegree;
	Standard_Integer myVDegree;

	DEFINE_STANDARD_RTTI(BSplineSurfaceContainer)

};


#endif
