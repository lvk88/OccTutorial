//OpenCASCADE Tutorials
//Laszlo Kudela
//Nov 19, 2015

#include <Chapter1_Basics/inc/LinePlaneIntersection.hpp>

LinePlaneIntersection::LinePlaneIntersection() {
	// TODO Auto-generated constructor stub

}

LinePlaneIntersection::~LinePlaneIntersection() {
	// TODO Auto-generated destructor stub
}

gp_Pnt LinePlaneIntersection::intersectLineWithPlane(const gp_Lin& line,
		const gp_Pln& plane) {
	//Get implicit equation of plane
	//A*X + B*Y + C*Z + D = 0
	Standard_Real A,B,C,D;
	plane.Coefficients(A,B,C,D);
}
