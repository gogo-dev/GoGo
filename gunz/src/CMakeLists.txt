set(GUNZ_SRC
	Channel.cpp
	ChannelList.cpp
	MUIDSanta.cpp
	PlayerTraits.cpp
	# More sources here!
)

add_library(gunz ${GUNZ_SRC})
target_link_libraries(gunz ${Boost_LIBRARIES})
