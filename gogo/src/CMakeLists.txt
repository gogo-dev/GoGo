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
	# Feel free to add more source files when they're added.
)

add_executable(gogo ${GOGO_SRC})

target_link_libraries(gogo
	util
	database
	cockpit
	${Boost_LIBRARIES}
)
