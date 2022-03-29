set(Authorization_source_files
    authorization.h
    authorization.cpp
)
add_library(Authorization ${Authorization_source_files})


target_link_libraries(Authorization AccountsDB)
target_link_libraries(Authorization Console)