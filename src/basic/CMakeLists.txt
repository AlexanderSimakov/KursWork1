set(basic_source_files
    helpFunctions.cpp
    helpFunctions.h
    ConsoleOut.cpp
    ConsoleOut.h
)
add_library(basic ${basic_source_files})

add_subdirectory(Account)
add_subdirectory(Product)

target_link_libraries(basic Account)
target_link_libraries(basic Product)
target_link_libraries(basic sql)
target_link_libraries(basic sha)