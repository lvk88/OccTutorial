#ifndef WRITECOORDINATESTOFILE_HPP
#define WRITECOORDINATESTOFILE_HPP 
//OpenCASCADE tutorials
//Laszlo Kudela
//November 2015

#include "TColgp_Array1OfPnt.hxx"

namespace WriteCoordinatesToFile
{
void writeCoordinatesToFile(std::string fileName,const TColgp_Array1OfPnt& points);
}
#endif
