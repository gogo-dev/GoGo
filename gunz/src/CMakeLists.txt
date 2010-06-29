set(GUNZ_SRC
	MUIDSanta.cpp
	# More sources here!
)

add_library(gunz ${GUNZ_SRC})
target_link_libraries(gunz
	util
	${Boost_LIBRARIES}
)
