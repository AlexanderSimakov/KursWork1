set(dataBases_source_files
    AccountsDB.cpp 
    AccountsDB.h
)
add_library(dataBases ${dataBases_source_files})

target_link_libraries(dataBases sqlwork)
target_link_libraries(dataBases sql)
target_link_libraries(dataBases basic)