set(NET_SRC
	PacketParameters.cpp
	PacketCrypto.cpp
	PacketRegistry.cpp
	all_packets.cpp
	# Feel free to add more source files when they're added.
)

add_library(net ${NET_SRC})
target_link_libraries(net
	util
)
