set(ConfirmationMenu_source_files
    ConfirmationMenu.cpp
    ConfirmationMenu.hpp
)
add_library(ConfirmationMenu ${ConfirmationMenu_source_files})

target_link_libraries(ConfirmationMenu Console)
target_link_libraries(ConfirmationMenu menu)