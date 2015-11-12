//OpenCASCADE tutorials by Laszlo Kudela
//2015 November
//Chapter 1.1 Basics

#include <iostream>

#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax2.hxx>
#include <gp_Circ.hxx>

int main(int argc, char *argv[])
{
	//We create a circle centered at (2.5,2.5) with a radius of 2.5	
	//A circle needs to know
	//its center (2.5,2.5)
	//its orientation (lies on the xy plane, i.e. its normal is the z axis)
	//its radius (2.5)
	
	gp_Pnt centerPoint(2.5,2.5,0);
	gp_Dir normalDirection(0.0,0.0,1.0);
	gp_Dir xDirection(1.0,0.0,0.0);
	gp_Ax2 axis(centerPoint,normalDirection,xDirection);

	//Creating the circle
	gp_Circ circle(axis,2.5);

	//Some convenience functions provided by the circle class
	std::cout << "Circle area is: " << circle.Area() << std::endl;
	std::cout << "Circle circumference is: " << circle.Length() << std::endl;

	//Create a scaled copy of the circle
	gp_Circ circle2 = circle.Scaled(gp_Pnt(2.5,2.5,0.0),2.0);		
	std::cout << "Scaled circle area is: " << circle2.Area() << std::endl;
	std::cout << "Scaled circle circumference is: " << circle2.Length() << std::endl;

			
	return 0;
}
