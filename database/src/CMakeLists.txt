set(database_SRC
	MySQLGunzDB.cpp
	# More sources here!
)

add_library(database ${database_SRC})
target_link_libraries(database
	util
	${Boost_LIBRARIES}
	${MYSQL_LIBRARIES}
	${MYSQL++_LIBRARIES}
)
