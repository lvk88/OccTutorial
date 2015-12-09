//OpenCASCADE tutorial by Laszlo Kudela
//December 2015

#include "../inc/StlPointsExtractor.hpp"

#include "Utilities/inc/catch.hpp"
#include "Utilities/inc/constants.hpp"

#include "TColgp_HArray1OfPnt.hxx"
#include "BRepPrimAPI_MakeBox.hxx"
#include "TopoDS_Shape.hxx"

TEST_CASE("CheckNumberOfPoints","[StlPointsExtractor]")
{
	//Create a simple box
	BRepPrimAPI_MakeBox boxMaker(10.0,20.0,30.0);
	TopoDS_Shape boxShape = boxMaker.Solid();

	Handle_TColgp_HArray1OfPnt extractedPoints = StlPointsExtractor::extractVerticesFromTopoDSShape(boxShape);

	REQUIRE(extractedPoints->Length() == 8);
}

TEST_CASE("CheckPointLocations","[StlPointsExtractor]")
{
	//Create a simple box
	BRepPrimAPI_MakeBox boxMaker(10.0,20.0,30.0);
	TopoDS_Shape boxShape = boxMaker.Solid();

	Handle_TColgp_HArray1OfPnt extractedPoints = StlPointsExtractor::extractVerticesFromTopoDSShape(boxShape);

	gp_Pnt point = extractedPoints->Value(1);

	REQUIRE(point.X() == Approx(0.0).epsilon(1E-12));
	REQUIRE(point.Y() == Approx(0.0).epsilon(1E-12));
	REQUIRE(point.Z() == Approx(30.0).epsilon(1E-12));

	point = extractedPoints->Value(2);
	REQUIRE(point.X() == Approx(0.0).epsilon(1E-12));
	REQUIRE(point.Y() == Approx(0.0).epsilon(1E-12));
	REQUIRE(point.Z() == Approx(0.0).epsilon(1E-12));

	point = extractedPoints->Value(7);
	REQUIRE(point.X() == Approx(10.0).epsilon(1E-12));
	REQUIRE(point.Y() == Approx(20.0).epsilon(1E-12));
	REQUIRE(point.Z() == Approx(30.0).epsilon(1E-12));

}

