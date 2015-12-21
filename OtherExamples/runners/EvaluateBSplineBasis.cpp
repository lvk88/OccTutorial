
//OpenCASCADE Tutorials by Laszlo Kudela
//December 2015

#include "Utilities/inc/MathFunctions.hpp"

#include "Chapter1_Basics/inc/CylinderToBspline.hpp"
#include "Chapter1_Basics/inc/BSplineSurfaceContainer.hpp"
#include "Chapter1_Basics/inc/BSplineBasisComputations.hpp"

#include "math_Matrix.hxx"
#include "BSplCLib.hxx"
#include "TColStd_HArray1OfInteger.hxx"
#include "TColStd_HArray1OfReal.hxx"

#include <iostream>
#include <fstream>


int main(int argc, char *argv[])
{
	//gp_Cylinder cylinder(gp_Ax3(gp::XOY()),50.0);
	//Handle_BSplineSurfaceContainer container = CylinderToBSpline::convertClosedCylinderToBSpline(cylinder,50.0);

	//Standard_Integer flatKnotSequenceLength = BSplCLib::KnotSequenceLength(container->myUMultiplicities->Array1(),2,true);
	//
	//Handle_TColStd_HArray1OfReal flatKnots = new TColStd_HArray1OfReal(1,flatKnotSequenceLength);
	//BSplCLib::KnotSequence(container->myUKnots->Array1(),container->myUMultiplicities->Array1(),2,true,flatKnots->ChangeArray1());	
	////BSplCLib::Reparametrize(0.0,1.0,flatKnots->ChangeArray1());
	//std::vector<double> samplePoints = MathFunctions::linspace(0.0,1.0,100);

	Handle_TColStd_HArray1OfReal flatKnots = new TColStd_HArray1OfReal(1,10);
	flatKnots->SetValue(2,0.0);
	flatKnots->SetValue(3,0.0);
	flatKnots->SetValue(4,1./3.);
	flatKnots->SetValue(5,1./3.);
	flatKnots->SetValue(6,2./3.);
	flatKnots->SetValue(7,2./3.);
	flatKnots->SetValue(8,1.0);
	flatKnots->SetValue(9,1.0);

	TColStd_Array1OfInteger mults(1,6);
	mults.SetValue(1,1);
	mults.SetValue(2,2);
	mults.SetValue(3,2);
	mults.SetValue(4,2);
	mults.SetValue(5,2);
	mults.SetValue(6,1);

	std::vector<double> samplePoints = MathFunctions::linspace(0.0,1.0,100);

	std::ofstream file;
	file.open("basisFunctions.txt");
	for(size_t basisFunctionNumber=0;basisFunctionNumber<7;basisFunctionNumber++)
	{
		file << basisFunctionNumber << std::endl;
		for(size_t i=0;i<samplePoints.size();i++)
		{
			Standard_Integer knotIndex;
			Standard_Real newParameter;
			double bSplineValue = BSplineBasisComputations::evaluateBasisFunction(flatKnots,2,samplePoints[i],basisFunctionNumber);
			file << bSplineValue << "\t";
		}
		file << std::endl;
		for(size_t i=0;i<samplePoints.size();i++)
		{
			file << samplePoints[i] << "\t";
		}
		file << std::endl;
	}
	std::cout << BSplCLib::NbPoles(2,true,mults) << std::endl;
}
