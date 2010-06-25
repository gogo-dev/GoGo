set(DATABASE_MYSQL_MODULES
	mysql_modules/CreateCharacter.cpp
	mysql_modules/GetAccountInfo.cpp
	mysql_modules/GetCharacterInfo.cpp
	mysql_modules/GetCharacterList.cpp
	mysql_modules/GetCID.cpp
	mysql_modules/GetEquipment.cpp
	mysql_modules/GetInventory.cpp
	mysql_modules/NameExists.cpp
	# More sources here!
)

set(DATABASE_POSTGRESQL_MODULES
	# More sources here!
)

set(DATABASE_MYSQL_SRC
	MySQLGunzDB.cpp
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
