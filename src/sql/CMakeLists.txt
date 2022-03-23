set(sqlwork_source_files
    SQLWork.cpp
    SQLWork.h
)
add_library(sqlwork ${sqlwork_source_files})

target_link_libraries(sqlwork sqlite)