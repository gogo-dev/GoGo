set(TESTS
	test_packet_parameter_construction
	# Add more tests here.
)

foreach(test ${TESTS})
	add_executable(${test} ${test})
	target_link_libraries(${test} net ${Boost_LIBRARIES})
	add_test(${test} ${test})
endforeach()
