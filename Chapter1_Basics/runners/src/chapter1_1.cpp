//OpenCASCADE tutorial by Laszlo Kudela
//November 2015

#include "../inc/chapter1_1.hpp"

#include "gp_Pnt.hxx"
#include "gp_Ax1.hxx"
#include "gp_Trsf.hxx"

#include<iostream>

chapter1_1::chapter1_1()
{

}
chapter1_1::~chapter1_1()
{

}

int chapter1_1::execute(int argc, char** argv)
{
	//Create two point classes, with (x,y,z) coordinates
	gp_Pnt pnt1(0.0,0.0,0.0);
	gp_Pnt pnt2(1.0,1.0,1.0);

	//Display their coordinates
  	std::cout << "pnt1: " << pnt1.X() << " " << pnt1.Y() << " " << pnt1.Z() << std::endl;	
  	std::cout << "pnt2: " << pnt2.X() << " " << pnt2.Y() << " " << pnt2.Z() << std::endl;	
	std::cout << "Distance between pnt1 and pnt2: " << pnt1.Distance(pnt2) << std::endl;

	//Rotate pnt1 around the point2, by 90 degrees 
  	gp_Trsf rotation;
	gp_Ax1 rotationAxis(gp_Pnt(1.0,1.0,0.0),gp_Dir(0.0,0.0,1.0));
	rotation.SetRotation(rotationAxis,3.1415926/2.0);	
	pnt1.Transform(rotation);
	std::cout << "pnt1 after rotation: " << pnt1.X() << " " << pnt1.Y() << " " << pnt1.Z()  << std::endl;

	//Create a new point by mirroring pnt1 about the y axis
	gp_Ax1 axisOfSymmetry(gp_Pnt(0.0,0.0,0.0),gp_Dir(0.0,1.0,0.0));
	gp_Pnt pnt3 = pnt1.Mirrored(axisOfSymmetry);
	std::cout << "pnt3 after mirroring: " << pnt3.X() << " " << pnt3.Y() << " " << pnt3.Z()  << std::endl;
	
	return 0;
}
