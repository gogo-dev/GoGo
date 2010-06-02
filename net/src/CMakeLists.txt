set(NET_SRC
	PacketParameters.cpp
	PacketCrypto.cpp
	PacketRegistry.cpp
	all_packets.cpp
	security.cpp
	# Feel free to add more source files when they're added.
)

# Used to speed up the compilation on gcc. Only downside is we lose
# variable debugging information in PacketRegistry.cpp. Not that huge
# of a loss.
if(CMAKE_COMPILER_IS_GNUCXX)
	set_source_files_properties(
		PacketRegistry.cpp

		PROPERTIES COMPILE_FLAGS "-fno-var-tracking"
	)
endif()

add_library(net ${NET_SRC})
target_link_libraries(net
	${Boost_LIBRARIES}
	util
)
