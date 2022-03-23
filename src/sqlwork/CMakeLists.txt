set(sqlwork_source_files
    SQLWORK.cpp
    SQLWORK.h
    AccountsDB.cpp
    AccountsDB.h
    ProductsDB.cpp
    ProductsDB.h
)
add_library(sqlwork ${sqlwork_source_files})

target_link_libraries(sqlwork sql)
target_link_libraries(sqlwork basic)