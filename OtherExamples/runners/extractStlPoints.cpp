//OpenCASCADE tutorials by Laszlo Kudela
//December 2015

#include "Chapter1_Basics/inc/WriteCoordinatesToFile.hpp"
#include "OtherExamples/inc/StlPointsExtractor.hpp"

#include "StlAPI.hxx"
#include "TColgp_HArray1OfPnt.hxx"

#include <iostream>

int main(int argc, char *argv[])
{
	
	if(argc < 2)
	{
		std::cout << "Usage: " << std::endl;
		std::cout << "extractStlPoints [InputSTLFile]" << std::endl;
		return 1;
	}

	char* inputFileName = argv[1];

	TopoDS_Shape stlShape;	
	std::cout << "Reading STL file " << inputFileName << " ..." << std::flush;

	StlAPI::Read(stlShape,inputFileName);

	std::cout << "done.";

	Handle_TColgp_HArray1OfPnt extractedPoints = StlPointsExtractor::extractVerticesFromTopoDSShape(stlShape);

	WriteCoordinatesToFile::writeCoordinatesToFile("stlOutput.txt",extractedPoints->Array1());
	
	return 0;
}
