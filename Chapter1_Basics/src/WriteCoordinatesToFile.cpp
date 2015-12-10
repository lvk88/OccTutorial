#include "Chapter1_Basics/inc/WriteCoordinatesToFile.hpp"

#include <fstream>
#include <string>

#include "TColgp_Array1OfPnt.hxx"
#include "TColgp_Array2OfPnt.hxx"

namespace WriteCoordinatesToFile
{
void writeCoordinatesToFile(std::string fileName,const TColgp_Array1OfPnt& points)
{
	std::ofstream file;
	file.open(fileName.c_str());
	for(Standard_Integer i = points.Lower();i <= points.Upper();i++)
	{
		file << points.Value(i).X() << " " << points.Value(i).Y() << " " << points.Value(i).Z() << std::endl;
	}
}

void writeCoordinatesToFile(std::string fileName,const TColgp_Array2OfPnt& points)
{
	std::ofstream file;
	file.open(fileName.c_str());
	for(Standard_Integer i=1;i<=points.ColLength();i++)
	{
		for(Standard_Integer j=1;j<=points.RowLength();j++)
		{
			gp_Pnt currentControlPoint = points.Value(i,j);
			file << currentControlPoint.X() << " " << currentControlPoint.Y() << " " << currentControlPoint.Z() << std::endl;
		}
	}


	return;

}
}
