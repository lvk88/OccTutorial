#ifndef WRITECOORDINATESTOFILE_HPP
#define WRITECOORDINATESTOFILE_HPP 
//OpenCASCADE tutorials
//Laszlo Kudela
//November 2015

#include <string>

class TColgp_Array1OfPnt;
class TColgp_Array2OfPnt;

namespace WriteCoordinatesToFile
{
void writeCoordinatesToFile(std::string fileName,const TColgp_Array1OfPnt& points);
void writeCoordinatesToFile(std::string fileName,const TColgp_Array2OfPnt& points);
}
#endif
