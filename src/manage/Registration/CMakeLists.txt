set(Registration_source_files
    registration.hpp
    registration.cpp
)
add_library(Registration ${Registration_source_files})


target_link_libraries(Registration AccountsDB)
target_link_libraries(Registration Console)