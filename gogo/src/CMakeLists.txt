set(GOGO_HEADERS
	ChannelLoader.h
	Configuration.h
	ConsoleLogger.h
	GoGoClient.h
	GoGoFactory.h
	error_codes.h
	# Feel free to add more header files when they're added.
)

set(GOGO_SRC
	ChannelLoader.cpp
	Configuration.cpp
	ConsoleLogger.cpp
	GoGoClient.cpp
	GoGoFactory.cpp
	main.cpp
	# Feel free to add more source files when they're added.
)

set(GOGO_MODULES
	modules/error_handling.cpp
	modules/handshake.cpp
	modules/messaging.cpp
	modules/OnMatchLogin.cpp
	modules/OnCharList.cpp
	modules/OnCharCreate.cpp
	modules/OnCharDelete.cpp
	modules/OnCharInfo.cpp
	modules/OnCharSelect.cpp
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
	gunz
	tinyxml
	${Boost_LIBRARIES}
)

# Moves the config files into the appropriate directory when either "make" or
# "make install" is called.

configure_file(../config/channel.xml channel.xml COPYONLY)
install(FILES ../config/channel.xml DESTINATION ${CMAKE_INSTALL_PREFIX})

configure_file(../config/gogo.conf gogo.conf COPYONLY)
install(FILES ../config/gogo.conf DESTINATION ${CMAKE_INSTALL_PREFIX})

configure_file(../config/my.sql my.sql COPYONLY)
install(FILES ../config/my.sql DESTINATION ${CMAKE_INSTALL_PREFIX})

configure_file(../config/postgre.sql postgre.sql COPYONLY)
install(FILES ../config/postgre.sql DESTINATION ${CMAKE_INSTALL_PREFIX})
