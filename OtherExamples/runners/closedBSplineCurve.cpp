//OpenCASCADE Tutorials by Laszlo Kudela
//December 2015
//
//

#include "Utilities/inc/MathFunctions.hpp"
#include "Chapter1_Basics/inc/WriteCoordinatesToFile.hpp"

#include "BSplCLib.hxx"
#include "TColgp_Array1OfPnt.hxx"
#include "TColStd_Array1OfReal.hxx"
#include "TColStd_Array1OfInteger.hxx"

int main(int argc, char *argv[])
{
	//Here, we create a closed B-Spline curve
	TColStd_Array1OfReal knots(1,3);
	knots.SetValue(1,0.0);
	knots.SetValue(2,1.0);
	knots.SetValue(3,2.0);

	double period = 2.0;

	TColStd_Array1OfInteger multiplicities(1,3);
	multiplicities.SetValue(1,3);
	multiplicities.SetValue(2,1);
	multiplicities.SetValue(3,3);

	TColgp_Array1OfPnt poles(1,4);
	poles.SetValue(1,gp_Pnt(0.0,0.0,0.0));
	poles.SetValue(2,gp_Pnt(1.0,0.5,0.0));
	poles.SetValue(3,gp_Pnt(0.5,1.0,0.0));
	poles.SetValue(4,gp_Pnt(0.0,1.0,0.0));

	std::vector<double> samples = MathFunctions::linspace(0.0,2.0,100.0);

	TColgp_Array1OfPnt samplePoints(1,samples.size());

	for(size_t i=0;i<samples.size();i++)
	{
		gp_Pnt evalPoint;
 		BSplCLib::D0(samples[i],0,2,false,poles,BSplCLib::NoWeights(),knots,multiplicities,evalPoint);
		samplePoints.SetValue(i+1,evalPoint);
		std::cout << samples[i] << " " <<  evalPoint.X() << " " << evalPoint.Y() << std::endl;
	}


	WriteCoordinatesToFile::writeCoordinatesToFile("closedSpline.txt",samplePoints);

	return 0;
}
