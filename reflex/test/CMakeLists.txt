set(REFLEX_TESTS
	test_buffer
	test_task_processor
	# Add more tests here.
)

add_executable(test_reflex ${REFLEX_TESTS})
target_link_libraries(test_reflex
	reflex
	gtest
	${Boost_LIBRARIES}
)
add_test(reflex test_reflex)
