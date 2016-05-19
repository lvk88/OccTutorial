//OpenCASCADE tutorials by Laszlo Kudela
//2016 May

#include "STEPControl_Reader.hxx"
#include "StlAPI_Writer.hxx"
#include "TopoDS_Shape.hxx"
#include "Standard_ConstructionError.hxx"

int main(int argc, char *argv[])
{
  STEPControl_Reader reader;
  reader.ReadFile(argv[1]);
  reader.TransferRoots();
  TopoDS_Shape stepShape = reader.OneShape();

  try
  {
  StlAPI_Writer writer;
  writer.Write(stepShape,argv[2]);
  }catch(Standard_ConstructionError& e)
  {
    std::cout << e.GetMessageString() << std::endl;
  }
  
  return 0;
}
