set(basic_source_files
    account.h
    product.h
    helpFunctions.cpp
    helpFunctions.h
    ConsoleOut.cpp
    ConsoleOut.h
)
add_library(basic ${basic_source_files})

target_link_libraries(basic sql)
target_link_libraries(basic sha)