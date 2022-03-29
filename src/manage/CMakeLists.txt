set(manage_source_files
    session.cpp
    session.h
)
add_library(manage ${manage_source_files})

add_subdirectory(AdminSession)
add_subdirectory(UserSession)
add_subdirectory(Authorization)
add_subdirectory(Registration)

target_link_libraries(manage sql)
target_link_libraries(manage AccountsDB)
target_link_libraries(manage ProductsDB)
target_link_libraries(manage Account)
target_link_libraries(manage Product)
target_link_libraries(manage Console)
target_link_libraries(manage menu)
target_link_libraries(manage ConfirmationMenu)
target_link_libraries(manage MenuFactory)