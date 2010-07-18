set(TINYXML_TESTS
	xmltest
	# More tests here!
)

add_executable(test_tinyxml ${TINYXML_TESTS})
target_link_libraries(test_tinyxml
	tinyxml
)
add_test(tinyxml test_tinyxml)

configure_file(utf8test.xml utf8test.xml COPYONLY)
configure_file(utf8testverify.xml utf8testverify.xml COPYONLY)
