# This file contains helper macros and functions used by every other CMakeList.

macro(add_gogo_executable exename sources)
	add_executable(${exename}
		${sources})
	target_link_libraries(${exename}
		${Boost_LIBRARIES})
	install(TARGETS ${exename}
		DESTINATION ${OUTPUT}
		PERMISSIONS WORLD_EXECUTE WORLD_READ WORLD_WRITE)
endmacro()

macro(add_gogo_library libname sources)
	add_library(${libname} ${sources})

	# MSVC auto-links, so only do this if we're using GNUCXX.
	if(CMAKE_COMPILER_IS_GNUCXX)
		target_link_libraries(${libname}
			${Boost_LIBRARIES})
	endif()
endmacro()
