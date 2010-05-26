set(UTIL_SRC
	ConsoleLogger.cpp
	# More sources here!
)

add_library(util ${UTIL_SRC})
target_link_libraries(util
	${Boost_LIBRARIES}
)
