#include "Chapter1_Basics/inc/WriteCoordinatesToFile.hpp"

#include <fstream>
#include <string>

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
}
