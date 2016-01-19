//OpenCASCADE tutorial by Laszlo Kudela
//January 2016

#include "../inc/GeometryWriter.hpp"

#include "Geom_Curve.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "STEPControl_Writer.hxx"

GeometryWriter::GeometryWriter()
{

}

GeometryWriter::~GeometryWriter()
{

}

void GeometryWriter::writeGeomEntityToStepFile(Handle_Geom_Curve curve, std::string fileName)
{
	BRepBuilderAPI_MakeEdge edgeMaker;
	edgeMaker.Init(curve);	
	TopoDS_Shape edge = edgeMaker.Shape();

	STEPControl_Writer writer;
	writer.Transfer(edge,STEPControl_AsIs);
	writer.Write(fileName.c_str());
	return;
}

void GeometryWriter::writeGeomEntityToStepFile(Handle_Geom_Surface surface, std::string fileName)
{
	BRepBuilderAPI_MakeFace faceMaker;
	faceMaker.Init(surface,true,1E-6);	
	TopoDS_Shape face = faceMaker.Shape();

	STEPControl_Writer writer;
	writer.Transfer(face,STEPControl_AsIs);
	writer.Write(fileName.c_str());
	return;
}
