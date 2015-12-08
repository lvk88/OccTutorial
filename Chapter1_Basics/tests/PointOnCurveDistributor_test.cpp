//OpenCASCADE tutorial by Laszlo Kudela
//November 2015

#include "Utilities/inc/catch.hpp"
#include "Utilities/inc/constants.hpp"

#include "../inc/PointOnCurveDistributor.hpp"

#include "gp_Pnt.hxx"
#include "gp_Circ.hxx"

TEST_CASE("Get points on circle","[chapter1]")
{
	gp_Circ circle(gp::XOY(),1.0);
	TColgp_Array1OfPnt points(1,5);
	PointOnCurveDistribution::distributePointsOnCurve(circle,points,0.0,2.0*PI,5);


	REQUIRE(points.Value(1).X() == Approx(1.0).epsilon(1E-12));
	REQUIRE(points.Value(1).Y() == Approx(0.0).epsilon(1E-12));
	REQUIRE(points.Value(1).Z() == Approx(0.0).epsilon(1E-12));

	REQUIRE(points.Value(2).X() == Approx(0.0).epsilon(1E-12));
	REQUIRE(points.Value(2).Y() == Approx(1.0).epsilon(1E-12));
	REQUIRE(points.Value(2).Z() == Approx(0.0).epsilon(1E-12));

	REQUIRE(points.Value(3).X() == Approx(-1.0).epsilon(1E-12));
	REQUIRE(points.Value(3).Y() == Approx(0.0).epsilon(1E-12));
	REQUIRE(points.Value(3).Z() == Approx(0.0).epsilon(1E-12));

	REQUIRE(points.Value(4).X() == Approx(0.0).epsilon(1E-12));
	REQUIRE(points.Value(4).Y() == Approx(-1.0).epsilon(1E-12));
	REQUIRE(points.Value(4).Z() == Approx(0.0).epsilon(1E-12));
}

