set(Account_source_files
    Account.h
    Account.cpp
)
add_library(Account ${Account_source_files})


target_link_libraries(Account sha)