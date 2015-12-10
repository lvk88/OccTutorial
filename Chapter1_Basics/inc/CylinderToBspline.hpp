//OpenCASCADE tutorials by Laszlo Kudela
//December 2015

#ifndef _CYLINDERTOBSPLINE_HPP
#define _CYLINDERTOBSPLINE_HPP 

#include "BSplineSurfaceContainer.hpp"

#include "gp_Cylinder.hxx"


class CylinderToBSpline
{
public:
	CylinderToBSpline ();
	virtual ~CylinderToBSpline ();

	static Handle_BSplineSurfaceContainer convertClosedCylinderToBSpline(const gp_Cylinder& cylinder, Standard_Real length);

private:
	/* data */
};

#endif
