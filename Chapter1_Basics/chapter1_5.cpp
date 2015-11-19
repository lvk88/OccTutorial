//OpenCASCADE Tutorials
//Laszlo Kudela
//Nov 19, 2015

#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pln.hxx>


#include "Chapter1_Basics/inc/LinePlaneIntersection.hpp"

#include <iostream>

int main(int argc, char **argv) {
	//Create a plane
	gp_Dir normalOfPlane(1.0,0.0,1.0);
	gp_Dir xDirectionOfPlane(1.0,0.0,-1.0);
	gp_Pnt pointOnPlane(1.0,0.0,0.0);
	gp_Ax3 coordinateSystemOfPlane(pointOnPlane,normalOfPlane,xDirectionOfPlane);
	gp_Pln plane(coordinateSystemOfPlane);

	//Create a line
	gp_Lin line(gp_Pnt(0.0,0.0,0.0),gp_Dir(1.0,0.0,1.0));

	gp_Pnt intersectionPoint = LinePlaneIntersection::intersectLineWithPlane(line,plane);

	std::cout << intersectionPoint.X() << " " << intersectionPoint.Y() << " " << intersectionPoint.Z() << std::endl;

	return 0;
}


