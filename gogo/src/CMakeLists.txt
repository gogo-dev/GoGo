set(GOGO_SRC
	main.cpp
	PacketParameters.h
	PacketParameters.cpp
	Structures.h
	Structures.cpp
	PacketCrypt.h
	PacketCrypt.cpp
	Client.h
	Client.cpp
	Server.h
	Server.cpp
	# Feel free to add more source files when they're added.
)

add_executable(gogo ${GOGO_SRC})
