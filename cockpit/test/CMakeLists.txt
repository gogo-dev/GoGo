set(COCKPIT_TESTS
	test_parameters
	test_crypto
	test_param_extraction
	# More tests here!
)

foreach(test ${COCKPIT_TESTS})
	add_executable(${test} ${test})
	target_link_libraries(${test}
		cockpit
		${Boost_LIBRARIES}
	)
	add_test(${test} ${test})
endforeach()
