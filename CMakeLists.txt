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
	${CMAKE_CURRENT_SOURCE_DIR}/cmake
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
  add_definitions(/EHa -D_WIN32_WINNT=0x0501)
else(MSVC)
  # TODO: Any add gcc flags you want in here. Optimization would be good ;)
  add_definitions(-Wall -Wextra -Werror -Wfatal-errors -pipe)
endif(MSVC)

# Add Source groups for lazy windows users.
source_group("Header Files" REGULAR_EXPRESSION .*\\.h)
source_group("Source Files" REGULAR_EXPRESSION .*\\.cxx|.*\\.cpp)

enable_testing()
add_subdirectory(gogo/src)
add_subdirectory(gogo/test)

add_subdirectory(util/src)
add_subdirectory(util/test)

add_subdirectory(database/src)
add_subdirectory(database/test)

add_subdirectory(net/src)
add_subdirectory(net/test)
