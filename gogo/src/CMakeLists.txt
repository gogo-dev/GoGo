include_directories(.)

source_group(src REGULAR_EXPRESSION "*.(h|c(pp)?)$")

set(GOGO_SRC
	main.cpp) # Feel free to add more source files when they're added.

add_executable(gogo ${GOGO_SRC})
