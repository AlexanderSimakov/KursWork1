set(UserSession_source_files
    UserSession.hpp
    UserSession.cpp
)
add_library(UserSession ${UserSession_source_files})


target_link_libraries(UserSession manage)
target_link_libraries(UserSession menu)