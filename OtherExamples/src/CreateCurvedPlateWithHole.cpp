//OpenCASCADE tutorial by Laszlo Kudela
//December 2015

#include "../inc/CreateCurvedPlateWithHole.hpp"

#include "TColgp_Array2OfPnt.hxx"
#include "Geom_BezierSurface.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "BRepPrimAPI_MakeCylinder.hxx"
#include "BRepAlgoAPI_Cut.hxx"
#include "TopoDS_Shape.hxx"

namespace CreateCurvedPlateWithHole
{

TopoDS_Shape createCurvedPlateWithHole()
{
	//Create a biquadratic bezier surface from control points
	TColgp_Array2OfPnt controlPoints(1,3,1,3);

	controlPoints.SetValue(1,1,gp_Pnt(-5.0,-5.0,0.0));
	controlPoints.SetValue(2,1,gp_Pnt(0.0,-5.0,0.0));
	controlPoints.SetValue(3,1,gp_Pnt(5.0,-5.0,0.0));

	controlPoints.SetValue(1,2,gp_Pnt(-5.0,0.0,0.0));
	controlPoints.SetValue(2,2,gp_Pnt(0.0,0.0,5.0));
	controlPoints.SetValue(3,2,gp_Pnt(5.0,0.0,0.0));

	controlPoints.SetValue(1,3,gp_Pnt(-5.0,5.0,0.0));
	controlPoints.SetValue(2,3,gp_Pnt(0.0,5.0,0.0));
	controlPoints.SetValue(3,3,gp_Pnt(5.0,5.0,0.0));

	Handle_Geom_BezierSurface surface = new Geom_BezierSurface(controlPoints);

	//Create a TopoDS_Shape out of the Bezier surface
	TopoDS_Shape face = BRepBuilderAPI_MakeFace(surface,1E-6);

	//Create a cylinder that will cut a hole in the surface
	BRepPrimAPI_MakeCylinder cylinderMaker(1.0,10.0);
	TopoDS_Shape cylinder = cylinderMaker.Shape();

	BRepAlgoAPI_Cut cutMaker(face,cylinder);

	TopoDS_Shape plateWithHole = cutMaker.Shape();	

	return plateWithHole;
}

}
