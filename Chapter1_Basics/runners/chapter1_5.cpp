//OpenCASCADE Tutorials
//Laszlo Kudela
//Nov 19, 2015

#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pln.hxx>
#include <StdFail_InfiniteSolutions.hxx>

#include "Chapter1_Basics/inc/LinePlaneIntersection.hpp"

#include <iostream>

void treatIntersectionSolution(
		LinePlaneIntersection::LinePlaneIntersectionSolution solution) {
	switch (solution.state) {
	case LinePlaneIntersection::LinePlaneIntersectionSolution::InfiniteSolutions:
		std::cout << "The line lies on the plane" << std::endl;
		break;
	case LinePlaneIntersection::LinePlaneIntersectionSolution::NoSolution:
		std::cout << "No intersection point found" << std::endl;
		break;
	case LinePlaneIntersection::LinePlaneIntersectionSolution::OneSolution:
		std::cout << "Intersection point is " << solution.intersectionPoint.X()
				<< " " << solution.intersectionPoint.Y() << " "
				<< solution.intersectionPoint.Z() << std::endl;
	}
}

int main(int argc, char **argv) {
	//Create a plane
	gp_Dir normalOfPlane(1.0, 0.0, 1.0);
	gp_Dir xDirectionOfPlane(1.0, 0.0, -1.0);
	gp_Pnt pointOnPlane(1.0, 0.0, 0.0);
	gp_Ax3 coordinateSystemOfPlane(pointOnPlane, normalOfPlane,
			xDirectionOfPlane);
	gp_Pln plane(coordinateSystemOfPlane);

	//Create a line
	gp_Lin line(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(1.0, 0.0, 1.0));
	LinePlaneIntersection::LinePlaneIntersectionSolution intersectionPoint = LinePlaneIntersection::intersectLineWithPlane(
			line, plane);
	treatIntersectionSolution(intersectionPoint);

	//Create a second line that lies on the plane
	gp_Lin line2(gp_Pnt(1.0, 0.0, 0.0), gp_Dir(1.0, 0.0, -1.0));
	intersectionPoint = LinePlaneIntersection::intersectLineWithPlane(line2,
			plane);
	treatIntersectionSolution(intersectionPoint);

	gp_Lin line3(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(1.0, 0.0, -1.0));
	intersectionPoint = LinePlaneIntersection::intersectLineWithPlane(line3,
			plane);
	treatIntersectionSolution(intersectionPoint);

	return 0;
}

