set(GUNZ_SRC
	ChannelTraits.cpp
	MatchMaker.cpp
	MUIDSanta.cpp
	PlayerTraits.cpp
	# More sources here!
)

add_library(gunz ${GUNZ_SRC})
target_link_libraries(gunz
	util
	${Boost_LIBRARIES}
)
