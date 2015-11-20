//OpenCASCADE Tutorials
//Laszlo Kudela
//Nov 19, 2015

#ifndef CHAPTER1_BASICS_INC_LINEPLANEINTERSECTION_HPP_
#define CHAPTER1_BASICS_INC_LINEPLANEINTERSECTION_HPP_

#include "gp_Pnt.hxx"
#include "gp_Lin.hxx"
#include "gp_Pln.hxx"

class LinePlaneIntersection {
public:
	LinePlaneIntersection();
	virtual ~LinePlaneIntersection();

	struct LinePlaneIntersectionSolution
	{
		enum SolutionState{
			OneSolution,
			NoSolution,
			InfiniteSolutions
		};
		gp_Pnt intersectionPoint;
		SolutionState state;
	};

	static LinePlaneIntersectionSolution intersectLineWithPlane(const gp_Lin& line, const gp_Pln& plane);
};

#endif /* CHAPTER1_BASICS_INC_LINEPLANEINTERSECTION_HPP_ */
