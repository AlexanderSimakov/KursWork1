set(basic_source_files
    Account.h
    Account.cpp
    Product.cpp
    Product.h
    helpFunctions.cpp
    helpFunctions.h
    ConsoleOut.cpp
    ConsoleOut.h
)
add_library(basic ${basic_source_files})

target_link_libraries(basic sql)
target_link_libraries(basic sha)