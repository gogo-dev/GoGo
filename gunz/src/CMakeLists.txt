set(GUNZ_SRC
	dummy.cpp
	# More sources here!
)

add_library(gunz ${GUNZ_SRC})
target_link_libraries(gunz ${Boost_LIBRARIES})
