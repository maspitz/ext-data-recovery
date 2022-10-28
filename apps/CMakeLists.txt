add_executable(ext-data-recovery ext-data-recovery.c)

target_link_libraries(ext-data-recovery journal ${COM_ERR_LIBRARIES} ${EXT2FS_LIBRARIES})

install(TARGETS ext-data-recovery RUNTIME DESTINATION bin)
