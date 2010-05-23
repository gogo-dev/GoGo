source_group(test REGULAR_EXPRESSION "*.(h|c(pp)?)$")

set(TESTS
	test_build_environment
	test_boost
	# Add more tests here.
)

foreach(test ${TESTS})
	add_gogo_executable(${test} ${test}.cpp)
	add_test(${test} ${test})
endforeach()
