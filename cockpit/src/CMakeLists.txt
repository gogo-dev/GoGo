set(COCKPIT_SRC
	packet/Parameters.cpp
	# More sources here!
)

add_library(cockpit ${COCKPIT_SRC})

target_link_libraries(cockpit
	util
	${Boost_LIBRARIES}
)