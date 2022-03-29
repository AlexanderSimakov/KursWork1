set(AdminSession_source_files
    AdminSession.h
    AdminSession.cpp
)
add_library(AdminSession ${AdminSession_source_files})


target_link_libraries(AdminSession manage)
target_link_libraries(AdminSession menu)