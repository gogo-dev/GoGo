set(GOGO_HEADERS
	Configuration.h
	ConsoleLogger.h
	GoGoClient.h
	GoGoFactory.h
	MUIDSanta.h
	Structures.h
	# Feel free to add more header files when they're added.
)

set(GOGO_SRC
	Configuration.cpp
	ConsoleLogger.cpp
	GoGoClient.cpp
	GoGoFactory.cpp
	main.cpp
	MUIDSanta.cpp
	# Feel free to add more source files when they're added.
)

set(GOGO_MODULES
	modules/handshake.cpp
	modules/OnMatchLogin.cpp
	# Feel free to add more source files when they're added.
)

source_group("Core/Source Files" FILES ${GOGO_SRC})
source_group("Core/Header Files" FILES ${GOGO_HEADERS})
source_group("modules" FILES ${GOGO_MODULES})

add_executable(gogo ${GOGO_SRC} ${GOGO_HEADERS} ${GOGO_MODULES})

target_link_libraries(gogo
	util
	database
	cockpit
	${Boost_LIBRARIES}
)
