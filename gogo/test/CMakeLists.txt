set(TESTS
	test_build_environment
	test_boost
	test_packet_parameter_construction
	# Add more tests here.
)

foreach(test ${TESTS})
	add_gogo_executable(${test} ${test}.cpp)
	add_test(${test} ${test})
endforeach()
