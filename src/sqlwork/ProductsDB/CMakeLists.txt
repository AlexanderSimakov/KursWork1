set(ProductsDB_source_files
    ProductsDB.cpp
    ProductsDB.h
)

add_library(ProductsDB ${ProductsDB_source_files})

target_link_libraries(ProductsDB sqlwork)
target_link_libraries(ProductsDB Product)
target_link_libraries(ProductsDB Console)