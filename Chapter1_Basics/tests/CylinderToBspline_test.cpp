//OpenCASCADE tutorial by Laszlo Kudela
//November 2015

#include <iostream>


#include "../inc/CylinderToBspline.hpp"
#include "../inc/BSplineSurfaceContainer.hpp"
#include "../inc/WriteCoordinatesToFile.hpp"

#include "Utilities/inc/catch.hpp"
#include "Utilities/inc/constants.hpp"

#include "gp_Cylinder.hxx"
#include "TColStd_HArray1OfReal.hxx"
#include "TColStd_HArray1OfInteger.hxx"
#include "TColgp_HArray2OfPnt.hxx"

TEST_CASE("CylinderToBSpline","[Chapter1]")
{
	gp_Cylinder cylinder(gp_Ax3(gp::XOY()),50.0);
	Handle_BSplineSurfaceContainer container;
	REQUIRE_NOTHROW( container = CylinderToBSpline::convertClosedCylinderToBSpline(cylinder,50.0));
	SECTION("Check if zero")
	{
		CHECK_FALSE(container.IsNull());
	}

	SECTION("Check degrees")
	{
		CHECK(container->myUDegree == 2);
		CHECK(container->myVDegree == 1);
	}

	SECTION("Check knot vector lengths")
	{
		CHECK(container->myUKnots->Length() == 4);
		CHECK(container->myVKnots->Length() == 2);
	}

	SECTION("Check knot values and multiplicities")
	{

		CHECK(container->myUKnots->Value(1) == Approx(0.0).epsilon(1E-12));
		CHECK(container->myUKnots->Value(2) == Approx(1.0/3.0).epsilon(1E-12));
		CHECK(container->myUKnots->Value(3) == Approx(2.0/3.0).epsilon(1E-12));
		CHECK(container->myUKnots->Value(4) == Approx(1.0).epsilon(1E-12));

		CHECK(container->myUMultiplicities->Value(1) == 2);
		CHECK(container->myUMultiplicities->Value(2) == 2);
		CHECK(container->myUMultiplicities->Value(3) == 2);
		CHECK(container->myUMultiplicities->Value(4) == 2);

		CHECK(container->myVKnots->Value(1) == Approx(0.0).epsilon(1E-12));
		CHECK(container->myVKnots->Value(2) == Approx(50.0).epsilon(1E-12));

		CHECK(container->myVMultiplicities->Value(1) == 2);
		CHECK(container->myVMultiplicities->Value(2) == 2);

	}

	SECTION("Check control points")
	{
		//for(Standard_Integer i=1;i<=container->myControlPoints->ColLength();i++)
		//{
		//	for(Standard_Integer j=1;j<=container->myControlPoints->RowLength();j++)
		//	{
		//		gp_Pnt currentControlPoint = container->myControlPoints->Value(i,j);
		//		std::cout << "(" << currentControlPoint.X() << "," << currentControlPoint.Y() << "," << currentControlPoint.Z() << ")" << "\t";
		//	}
		//	std::cout << std::endl;
		//}
		//WriteCoordinatesToFile::writeCoordinatesToFile("controlPoints.txt",container->myControlPoints->Array2());

	}
}


