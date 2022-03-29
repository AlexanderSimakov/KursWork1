set(menu_source_files
    menu.cpp
    menu.h
)
add_library(menu ${menu_source_files})

add_subdirectory(confirm)
add_subdirectory(factory)

target_link_libraries(menu Console)