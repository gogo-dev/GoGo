include_directories(.)

source_group(src REGULAR_EXPRESSION *.*)

set(GOGO_SRC
	main.cpp) # Feel free to add more source files when they're added.

add_executable(gogo ${GOGO_SRC})
