set(MenuFactory_source_files
    MenuFactory.cpp
    MenuFactory.hpp
)
add_library(MenuFactory ${MenuFactory_source_files})

target_link_libraries(MenuFactory menu)