//OpenCASCADE tutorial by Laszlo Kudela
//November 2015
#ifndef _EXAMPLERUNNER_IMPL_HPP
#define _EXAMPLERUNNER_IMPL_HPP

template<typename T> 
int ExampleRunner::executeExample(int argc, char** argv)
{
	T exampleClass;
	return exampleClass.execute(argc,argv);
}
#endif
