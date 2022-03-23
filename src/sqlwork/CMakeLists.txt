set(sqlwork_source_files
    SQLWORK.cpp
    SQLWORK.h
)
add_library(sqlwork ${sqlwork_source_files})

target_link_libraries(sqlwork sql)