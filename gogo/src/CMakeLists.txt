set(GOGO_HEADERS
	Configuration.h
	ConsoleLogger.h
	GoGoClient.h
	GoGoFactory.h
	error_codes.h
	# Feel free to add more header files when they're added.
)

set(GOGO_SRC
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
	${Boost_LIBRARIES}
)

# Moves gogo.conf into the appropriate directory when either "make" or "make install" is called.
configure_file(gogo.conf gogo.conf COPYONLY)
install(FILES gogo.conf DESTINATION ${CMAKE_INSTALL_PREFIX})

configure_file(../db/gunzdb.sql gunzdb.sql COPYONLY)
install(FILES ../db/gunzdb.sql DESTINATION ${CMAKE_INSTALL_PREFIX})
