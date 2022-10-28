set(HEADER_LIST "${CMAKE_SOURCE_DIR}/include/journal/journal.h")

add_library(journal journal.c revoke.c recovery.c ${HEADER_LIST})

#target_include_directories(journal PUBLIC ../include)

target_link_libraries(journal ${UUID_LIBRARIES} ${BLKID_LIBRARIES})

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST})
