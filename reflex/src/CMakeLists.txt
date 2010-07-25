set(REFLEX_SRC
	Scheduler.cpp
	TaskProcessor.cpp
	# More sources here!
)

add_library(reflex ${REFLEX_SRC})
target_link_libraries(reflex ${Boost_LIBRARIES})