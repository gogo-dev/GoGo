set(DATABASE_MYSQL_MODULES
	MySQL/modules/CreateCharacter.cpp
	MySQL/modules/GetAccountInfo.cpp
	MySQL/modules/GetCharacterInfo.cpp
	MySQL/modules/GetCharacterList.cpp
	MySQL/modules/GetCID.cpp
	MySQL/modules/GetEquipment.cpp
	MySQL/modules/GetInventory.cpp
	MySQL/modules/NameExists.cpp
	# More sources here!
)

set(DATABASE_POSTGRESQL_MODULES
	# More sources here!
)

set(DATABASE_MYSQL_SRC
	MySQLGunzDB.cpp
	MySQL/ConnectionPool.cpp
	${DATABASE_MYSQL_MODULES}
	# More sources here!
)

set(DATABASE_POSTGRESQL_SRC
	${DATABASE_POSTGRESQL_MODULES}
	# More sources here!
)

set(database_SRC
	${DATABASE_MYSQL_SRC}
	${DATABASE_POSTGRESQL_SRC}
)

add_library(database ${database_SRC})
target_link_libraries(database
	util
	${Boost_LIBRARIES}
	${MYSQL_LIBRARIES}
	${MYSQL++_LIBRARIES}
)
