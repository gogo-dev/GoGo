set(TESTS
	test_build_environment
	test_boost
	test_channel_loader
	test_configuration
	# Add more tests here.
)

foreach(test ${TESTS})
	add_executable(${test} ${test})
	target_link_libraries(${test}
		util
		database
		cockpit
		gunz
		tinyxml
		${Boost_LIBRARIES}
	)
	add_test(${test} ${test})
endforeach()
