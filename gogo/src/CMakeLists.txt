set(GOGO_SRC
	main.cpp
	PacketParameters.h
	PacketParameters.cpp
	Structures.h
	PacketCrypt.h
	PacketCrypt.cpp
	# Feel free to add more source files when they're added.
)

add_executable(gogo ${GOGO_SRC})
