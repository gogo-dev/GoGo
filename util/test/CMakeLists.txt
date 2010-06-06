set(UTIL_TESTS
	test_memory
	# Add more tests here.
)

foreach(test ${UTIL_TESTS})
	add_executable(${test} ${test})
	target_link_libraries(${test} ${Boost_LIBRARIES})
	add_test(${test} ${test})
endforeach()
