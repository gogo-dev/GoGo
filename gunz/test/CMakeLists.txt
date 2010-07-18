set(GUNZ_TESTS
	test_channel_list
	test_muid_santa
	# Add more tests here.
)

add_executable(test_gunz ${GUNZ_TESTS})
target_link_libraries(test_gunz
	gunz
	gtest
	${Boost_LIBRARIES}
)
add_test(gunz test_gunz)
