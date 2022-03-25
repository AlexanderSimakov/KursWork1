set(basic_source_files
    helpFunctions.cpp
    helpFunctions.h
)
add_library(basic ${basic_source_files})

add_subdirectory(Account)
add_subdirectory(Product)
add_subdirectory(Console)

target_link_libraries(basic Account)
target_link_libraries(basic Product)
target_link_libraries(basic Console)
target_link_libraries(basic sql)
target_link_libraries(basic sha)