set(sqlwork_source_files
    SQLWORK.cpp
    SQLWORK.hpp
)
add_library(sqlwork ${sqlwork_source_files})

add_subdirectory(AccountsDB)
add_subdirectory(ProductsDB)

target_link_libraries(sqlwork sql)