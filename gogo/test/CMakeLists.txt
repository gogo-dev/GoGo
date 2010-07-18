set(GOGO_TESTS
	test_boost
	test_channel_loader
	test_configuration
	# Add more tests here.
)

add_executable(test_gogo ${GOGO_TESTS})
target_link_libraries(test_gogo
	util
	database
	cockpit
	gtest
	gunz
	tinyxml
	${Boost_LIBRARIES}
)
add_test(gogo test_gogo)
