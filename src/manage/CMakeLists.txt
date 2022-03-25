set(manage_source_files
    authorization.cpp
    authorization.h
    registration.cpp
    registration.h
    session.cpp
    session.h
)
add_library(manage ${manage_source_files})

target_link_libraries(manage sql)
target_link_libraries(manage Account)
target_link_libraries(manage Product)
target_link_libraries(manage Console)
target_link_libraries(manage menu)