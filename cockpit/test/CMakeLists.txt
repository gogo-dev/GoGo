set(COCKPIT_TESTS
	test_crypto.cpp
	test_param_extraction.cpp
	test_parameters.cpp
	test_registry.cpp
	# More tests here!
)

add_executable(test_cockpit ${COCKPIT_TESTS})
target_link_libraries(test_cockpit
	cockpit
	gtest
	${Boost_LIBRARIES}
)
add_test(cockpit test_cockpit)
