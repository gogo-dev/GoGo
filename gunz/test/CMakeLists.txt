set(GUNZ_TESTS
	# Add more tests here.
)

foreach(test ${GUNZ_TESTS})
	add_executable(${test} ${test})
	target_link_libraries(${test} ${Boost_LIBRARIES})
	add_test(${test} ${test})
endforeach()
