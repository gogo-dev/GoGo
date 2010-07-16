cmake_minimum_required(VERSION 2.6)
project(gogo)

set(PACKAGE_NAME gogo)
set(PACKAGE_BUGREPORT "http://code.google.com/p/gunzemulator/issues/list")

set(OUTPUT "${CMAKE_SOURCE_DIR}/bin")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE)
  message(FATAL_ERROR "In-source builds are not allowed.
CMake would overwrite the makefiles distributed with GoGo.
Please create a directory and run cmake from there, passing the path
to this source directory as the last argument.
This process created the file `CMakeCache.txt' and the directory `CMakeFiles'.
Please delete them.")
endif()

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
)

include(cmake/common.cmake)

if(MSVC)
	# TODO(Clark): FIX BOOST
	option("Boost is broken on VS. Clark is working on a fix." TRUE)
else()
	set(BOOST_VERSION 1.37.0)
	#set(Boost_USE_STATIC_LIBS ON)
	#set(Boost_USE_MULTITHREADED ON)
	find_package(Boost ${BOOST_VERSION} REQUIRED
		COMPONENTS filesystem iostreams program_options regex
		serialization signals thread wave) # python isn't used b/c that requires linking to a python library. Too much work ;)
	include_directories(${Boost_INCLUDE_DIR})
endif()

set(MYSQL_VERSION 5.0)
find_package(MySQL ${MYSQL_VERSION} REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})

set(MYSQL++_VERSION 3.0)
find_package(MySQL++ ${MYSQL++_VERSION} REQUIRED)
include_directories(${MYSQL++_INCLUDE_DIR})

# Add the "include" folder to the compiler search path to make everyone's life
# easier.
include_directories("include")

if(MSVC)
  # TODO: Add any msvc flags you want in here. Optimization would be good ;)
  add_definitions(/EHa -D_WIN32_WINNT=0x0501 /bigobj /wd4800 /W4 /w)
else(MSVC)
  # TODO: Any add gcc flags you want in here. Optimization would be good ;)
  add_definitions(-Wall -Wextra -Wfatal-errors -ansi -pedantic -pipe
	  -Wnon-virtual-dtor -Wreorder -Wchar-subscripts -Wcomment -Wformat
	  -Wimplicit -Wparentheses -Wno-long-long -Wpointer-arith -Wcast-qual
	  -Wdisabled-optimization)

  #  try_compile(
  #    COMPILER_SUPPORTS_LTO ${CMAKE_BINARY_DIR}
  # ${CMAKE_CURRENT_SOURCE_DIR}/cmake/empty_program.cpp
  # COMPILE_DEFINITIONS -flto -fwhole-program
  #)

  #list(APPEND CMAKE_C_FLAGS_DEBUG -O0 -DDEBUG)
  #list(APPEND CMAKE_CXX_FLAGS_DEBUG -O0 -DDEBUG)

  #list(APPEND CMAKE_C_FLAGS_RELEASE -finline-functions -funroll-loops -funswitch-loops)
  #list(APPEND CMAKE_CXX_FLAGS_RELEASE -finline-functions -funroll-loops -funswitch-loops)

  #if(COMPILER_SUPPORTS_LTO)
  # list(APPEND CMAKE_C_FLAGS_RELEASE -flto -fwhole-program)
  # list(APPEND CMAKE_CXX_FLAGS_RELEASE -flto -fwhole-program)
  #endif()

endif()

#message("BUILD TYPE: " ${CMAKE_BUILD_TYPE})
#message("C FLAGS (Global): " ${CMAKE_C_FLAGS})
#message("C FLAGS (Debug): " ${CMAKE_C_FLAGS_DEBUG})
#message("C FLAGS (Release): " ${CMAKE_C_FLAGS_RELEASE})
#message("")
#message("CXX FLAGS (Global): " ${CMAKE_CXX_FLAGS})
#message("CXX FLAGS (Debug): " ${CMAKE_C_FLAGS_DEBUG})
#message("CXX FLAGS (Release): " ${CMAKE_CXX_FLAGS_RELEASE})

# Build version.h
execute_process(COMMAND git describe --tags --dirty
	OUTPUT_VARIABLE GOGO_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

try_compile(PLATFORM_SUPPORTS_INTERLOCKEDINCREMENT64 ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/test_for_InterlockedIncrement64.cpp)

configure_file(cmake/version.h ${CMAKE_SOURCE_DIR}/include/version.h)
configure_file(cmake/platform.h ${CMAKE_SOURCE_DIR}/include/platform.h)

# Add Source groups for lazy windows users.
source_group("Header Files" REGULAR_EXPRESSION .*\\.h)
source_group("Source Files" REGULAR_EXPRESSION .*\\.cxx|.*\\.cpp)

enable_testing()

add_subdirectory(cockpit/src)
add_subdirectory(cockpit/test)

add_subdirectory(database/src)
add_subdirectory(database/test)

add_subdirectory(gogo/src)
add_subdirectory(gogo/test)

add_subdirectory(gtest/src)
add_subdirectory(gtest/test)

add_subdirectory(gunz/src)
add_subdirectory(gunz/test)

add_subdirectory(tinyxml/src)
add_subdirectory(tinyxml/test)

add_subdirectory(util/src)
add_subdirectory(util/test)