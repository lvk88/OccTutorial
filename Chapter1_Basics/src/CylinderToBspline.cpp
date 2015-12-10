//OpenCASCADE tutorials by Laszlo Kudela
//December 2015

#include "../inc/CylinderToBspline.hpp"
#include "Utilities/inc/constants.hpp"

#include "BSplCLib.hxx"
#include "TColStd_HArray2OfReal.hxx"
#include "TColStd_HArray1OfInteger.hxx"
#include "TColStd_HArray1OfReal.hxx"
#include "TColgp_HArray2OfPnt.hxx"
#include "Convert_CylinderToBSplineSurface.hxx"

#include <iostream>

CylinderToBSpline::CylinderToBSpline()
{

}
CylinderToBSpline::~CylinderToBSpline()
{

}

Handle_BSplineSurfaceContainer CylinderToBSpline::convertClosedCylinderToBSpline(const gp_Cylinder& cylinder, Standard_Real length)
{
	Convert_CylinderToBSplineSurface converter(cylinder,0.0,length);

	Standard_Integer uDegree = converter.UDegree();
	Standard_Integer vDegree = converter.VDegree();

	Handle_TColgp_HArray2OfPnt controlPoints = new TColgp_HArray2OfPnt(1,converter.NbUPoles(),1,converter.NbVPoles());
	Handle_TColStd_HArray2OfReal weights = new TColStd_HArray2OfReal(1,converter.NbUPoles(),1,converter.NbVPoles());
	Handle_TColStd_HArray1OfReal uKnots = new TColStd_HArray1OfReal(1,converter.NbUKnots());
	Handle_TColStd_HArray1OfReal vKnots = new TColStd_HArray1OfReal(1,converter.NbVKnots());
	Handle_TColStd_HArray1OfInteger uMultiplicities = new TColStd_HArray1OfInteger(1,converter.NbUKnots());
	Handle_TColStd_HArray1OfInteger vMultiplicities = new TColStd_HArray1OfInteger(1,converter.NbUKnots());

	for(Standard_Integer i=1;i<=converter.NbUKnots();i++)
	{
		uKnots->SetValue(i,converter.UKnot(i));
		uMultiplicities->SetValue(i,converter.UMultiplicity(i));
	}

	for(Standard_Integer i=1;i<=converter.NbVKnots();i++)
	{
		vKnots->SetValue(i,converter.VKnot(i));
		vMultiplicities->SetValue(i,converter.VMultiplicity(i));
	}


	for(Standard_Integer i=1;i<=converter.NbUPoles();i++)
	{
		for(Standard_Integer j=1;j<=converter.NbVPoles();j++)
		{
			controlPoints->SetValue(i,j,converter.Pole(i,j));
		}
	}		

	BSplCLib::Reparametrize(0.0,1.0,uKnots->ChangeArray1());

	Handle_BSplineSurfaceContainer result = new BSplineSurfaceContainer(controlPoints,weights,uKnots,vKnots,uMultiplicities,vMultiplicities,uDegree,vDegree);
	return result;

}
