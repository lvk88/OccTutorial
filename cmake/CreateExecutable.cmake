CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

function(CreateExecutable EXECUTABLESOURCE)
	
	get_filename_component(EXECUTABLEBINARY ${EXECUTABLESOURCE} NAME_WE)

	add_executable(${EXECUTABLEBINARY} ${EXECUTABLESOURCE})
	target_link_libraries(${EXECUTABLEBINARY} ${ARGN})

endfunction(CreateExecutable)
