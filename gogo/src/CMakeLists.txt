set(GOGO_SRC
	main.cpp
	custom_new.cpp
	Structures.h
	Client.h
	Client.cpp
	Server.h
	Server.cpp
	MUIDSanta.h
	MUIDSanta.cpp
	# Feel free to add more source files when they're added.
)

add_executable(gogo ${GOGO_SRC})
target_link_libraries(gogo
	util
	${Boost_LIBRARIES}
	${MySQL_LIBRARIES}
	${MySQL++_LIBRARIES}
)
