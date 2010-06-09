set(UTIL_SRC
	buffer.cpp
	# More sources here!
)

add_library(util ${UTIL_SRC})
target_link_libraries(util ${Boost_LIBRARIES})
