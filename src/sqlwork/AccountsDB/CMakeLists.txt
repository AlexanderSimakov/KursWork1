set(AccountsDB_source_files
    AccountsDB.h
    AccountsDB.cpp
)
add_library(AccountsDB ${AccountsDB_source_files})

target_link_libraries(AccountsDB sqlwork)
target_link_libraries(AccountsDB Account)
target_link_libraries(AccountsDB Console)