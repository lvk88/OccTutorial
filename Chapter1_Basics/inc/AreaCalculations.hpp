#ifndef AREACALCULATIONS_HPP
#define AREACALCULATIONS_HPP 
//OpenCASCADE tutorials
//Laszlo Kudela
//November 2015

#include "TColgp_HArray1OfPnt.hxx"

namespace AreaCalculations
{
double calculateTriangleArea(const Handle_TColgp_HArray1OfPnt triangleCorners);
}
#endif
