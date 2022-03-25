set(basic_source_files
    Product.cpp
    Product.h
    helpFunctions.cpp
    helpFunctions.h
    ConsoleOut.cpp
    ConsoleOut.h
)
add_library(basic ${basic_source_files})

add_subdirectory(Account)

target_link_libraries(basic Account)
target_link_libraries(basic sql)
target_link_libraries(basic sha)