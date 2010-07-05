set(GUNZ_SRC
	ChannelList.cpp
	ChannelTraits.cpp
	MUIDSanta.cpp
	PlayerList.cpp
	# More sources here!
)

add_library(gunz ${GUNZ_SRC})
target_link_libraries(gunz
	util
	${Boost_LIBRARIES}
)
