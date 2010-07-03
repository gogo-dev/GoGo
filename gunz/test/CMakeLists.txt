set(GUNZ_TESTS
	test_channel_list
	# Add more tests here.
)

foreach(test ${GUNZ_TESTS})
	add_executable(${test} ${test})
	target_link_libraries(${test}
		gunz
		${Boost_LIBRARIES})
	add_test(${test} ${test})
endforeach()
