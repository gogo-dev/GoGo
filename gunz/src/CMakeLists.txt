set(GUNZ_SRC
	Channel.cpp
	ChannelList.cpp
	MUIDSanta.cpp
	Player.cpp
	Stage.cpp
	# More sources here!
)

add_library(gunz ${GUNZ_SRC})
target_link_libraries(gunz
	util
	${Boost_LIBRARIES}
)
