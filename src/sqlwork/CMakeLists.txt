set(sqlwork_source_files
    SQLWORK.cpp
    SQLWORK.h
    ProductsDB.cpp
    ProductsDB.h
)
add_library(sqlwork ${sqlwork_source_files})

add_subdirectory(AccountsDB)

target_link_libraries(sqlwork sql)
target_link_libraries(sqlwork Product)
target_link_libraries(sqlwork Console)