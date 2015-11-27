#include "gp_Pnt.hxx"
#include "gp_Ax2.hxx"
#include "gp_Dir.hxx"
#include "gp_Elips.hxx"
#include "ElCLib.hxx"

#include "Utilities/inc/constants.hpp"

int main(int argc, char *argv[])
{
	//Exercise: create an ellipse from the gp package, evaluate 25 points on its circumference together
	//with the local NORMAL vectors that are pointing outwards. Note: to get the normal vector, simply rotate 
	//the tangent by 90 degrees clockwise
	
	gp_Pnt centerPoint(0.0,0.0,0.0);
	gp_Dir xDirection(1.0,1.0,0.0);
	gp_Dir normalDirection(0.0,0.0,1.0);
	gp_Ax2 axis(centerPoint,normalDirection,xDirection);

	gp_Elips ellipse(axis,4.0,2.0);

 	Standard_Integer numberOfSamplePoints = 20;
	double deltaU = 2*PI/(numberOfSamplePoints - 1);

	std::ofstream file;
	file.open("ellipsePoints.txt");

	for(Standard_Integer i = 0; i<numberOfSamplePoints;i++)
	{
		gp_Pnt pointOnEllipse;
		gp_Vec tangentVector;
		ElCLib::D1(i*deltaU,ellipse,pointOnEllipse,tangentVector);
		tangentVector.Rotate(gp_Ax1(pointOnEllipse,normalDirection),-PI/2);
		tangentVector.Divide(tangentVector.Magnitude());
		file << pointOnEllipse.X() << " " << pointOnEllipse.Y() << " " << pointOnEllipse.Z() << " " << tangentVector.X() << " " << tangentVector.Y() 
			<< " " << tangentVector.Z() << std::endl;
	}
	file.close();
	
	return 0;
}
