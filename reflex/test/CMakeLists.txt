set(REFLEX_TESTS
	test_buffer
	# Add more tests here.
)

add_executable(test_reflex ${REFLEX_TESTS})
target_link_libraries(test_reflex
	reflex
	gtest
	${Boost_LIBRARIES}
)
add_test(reflex test_reflex)
