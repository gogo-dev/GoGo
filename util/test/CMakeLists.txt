set(UTIL_TESTS
	test_memory
	# Add more tests here.
)

add_executable(test_util ${UTIL_TESTS})
target_link_libraries(test_util
	gtest
	${Boost_LIBRARIES}
)
add_test(util test_util)
