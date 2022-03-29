set(MenuFactory_source_files
    MenuFactory.cpp
    MenuFactory.h
)
add_library(MenuFactory ${MenuFactory_source_files})

target_link_libraries(MenuFactory menu)