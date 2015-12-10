//OpenCASCADE tutorial by Laszlo Kudela
//December 2015

#include "TColStd_HArray1OfReal.hxx"
#include <iostream>

#include "Utilities/inc/catch.hpp"
#include "Utilities/inc/constants.hpp"

#include "../inc/BSplineBasisComputations.hpp"
#include "../inc/WriteCoordinatesToFile.hpp"

TEST_CASE("BezierBasis","[Chapter 1]")
{
	Handle_TColStd_HArray1OfReal knots = new TColStd_HArray1OfReal(1,6);
	knots->SetValue(1,0.0);
	knots->SetValue(2,0.0);
	knots->SetValue(3,0.0);

	knots->SetValue(4,1.0);
	knots->SetValue(5,1.0);
	knots->SetValue(6,1.0);

	SECTION("Evaluate zeroth basis")
	{
		double value = BSplineBasisComputations::evaluateBasisFunction(knots,2,0.0,0);
		CHECK(value == Approx(1.0).epsilon(1E-12));

		value = BSplineBasisComputations::evaluateBasisFunction(knots,2,0.5,0);
		CHECK(value == Approx(0.25).epsilon(1E-12));

		value = BSplineBasisComputations::evaluateBasisFunction(knots,2,1.0,0);
		CHECK(value == Approx(0.0).epsilon(1E-12));
	}

	SECTION("Evaluate first basis")
	{
		double value = BSplineBasisComputations::evaluateBasisFunction(knots,2,0.0,1);
		CHECK(value == Approx(0.0).epsilon(1E-12));

		value = BSplineBasisComputations::evaluateBasisFunction(knots,2,0.5,1);
		CHECK(value == Approx(0.5).epsilon(1E-12));

		value = BSplineBasisComputations::evaluateBasisFunction(knots,2,1.0,1);
		CHECK(value == Approx(0.0).epsilon(1E-12));
	}

	SECTION("Evaluate second basis")
	{
		double value = BSplineBasisComputations::evaluateBasisFunction(knots,2,0.0,2);
		CHECK(value == Approx(0.0).epsilon(1E-12));

		value = BSplineBasisComputations::evaluateBasisFunction(knots,2,0.5,2);
		CHECK(value == Approx(0.25).epsilon(1E-12));

		value = BSplineBasisComputations::evaluateBasisFunction(knots,2,1.0,2);
		CHECK(value == Approx(1.0).epsilon(1E-12));
	}
}
