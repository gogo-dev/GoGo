set(GOGO_SRC
	Configuration.cpp
	Configuration.h
	ConsoleLogger.cpp
	ConsoleLogger.h
	GoGoClient.cpp
	GoGoClient.h
	GoGoFactory.cpp
	GoGoFactory.h
	main.cpp
	MUIDSanta.cpp
	MUIDSanta.h
	Structures.h

	modules/handshake.cpp
	modules/OnMatchLogin.cpp
	# Feel free to add more source files when they're added.
)

#Core subdirectory for VS
source_group("Core\\Source Files" FILES main.cpp Configuration.cpp ConsoleLogger.cpp GoGoFactory.cpp MUIDSanta.cpp GoGoClient.cpp)
source_group("Core\\Headers Files" FILES Configuration.h ConsoleLogger.h GoGoFactory.h Structures.h MUIDSanta.h GoGoClient.h)

source_group("Packet Handlers\\Source Files" FILES modules/handshake.cpp modules/OnMatchLogin.cpp)
source_group("Packet Handlers\\Header Files" FILES )

add_executable(gogo ${GOGO_SRC})

target_link_libraries(gogo
	util
	database
	cockpit
	${Boost_LIBRARIES}
)
