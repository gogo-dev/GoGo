set(TINYXML_TESTS
	xmltest.cpp
	# More tests here!
)

foreach(test ${TINYXML_TESTS})
	add_executable(${test} ${test})
	target_link_libraries(${test}
		tinyxml
	)
	add_test(${test} ${test})
endforeach()

configure_file(utf8test.xml utf8test.xml COPYONLY)
configure_file(utf8testverify.xml utf8testverify.xml COPYONLY)
