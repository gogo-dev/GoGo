set(COCKPIT_SRC
	packet/all_packets.cpp
	packet/crypto.cpp
	packet/Parameters.cpp
	packet/Registry.cpp
	packet/security.cpp

	Allocator.cpp
	Allocator.h
	Client.cpp
	Client.h
	MatchServer.cpp
	# More sources here!
)

# Used to speed up the compilation on gcc. Only downside is we lose
# variable debugging information in PacketRegistry.cpp. Not that huge
# of a loss.
if(CMAKE_COMPILER_IS_GNUCXX)
	set_source_files_properties(
		packet/Registry.cpp

		PROPERTIES COMPILE_FLAGS "-fno-var-tracking"
	)
endif()

add_library(cockpit ${COCKPIT_SRC})

target_link_libraries(cockpit
	util
	${Boost_LIBRARIES}
)
