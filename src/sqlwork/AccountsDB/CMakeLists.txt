set(AccountsDB_source_files
    AccountsDB.hpp
    AccountsDB.cpp
)
add_library(AccountsDB ${AccountsDB_source_files})

target_link_libraries(AccountsDB sqlwork)
target_link_libraries(AccountsDB Product)
target_link_libraries(AccountsDB Console)