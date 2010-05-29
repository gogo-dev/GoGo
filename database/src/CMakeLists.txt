set(database_SRC
	MySQLGunzDB.cpp
	# More sources here!
)

add_library(database ${database_SRC})
target_link_libraries(database ${Boost_LIBRARIES})
target_link_libraries(database ${MySQL_LIBRARIES})
target_link_libraries(database ${MySQL++_LIBRARIES})
