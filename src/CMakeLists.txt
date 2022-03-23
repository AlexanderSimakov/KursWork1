cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(CourseWork_exe)

add_subdirectory(basic)
add_subdirectory(manage)
add_subdirectory(menu)
add_subdirectory(sqlwork)
add_subdirectory(sqlite)
add_subdirectory(sha)

set(CourseWork_source_files Source.cpp)
add_executable(CourseWork ${CourseWork_source_files})

target_link_libraries(CourseWork basic)
target_link_libraries(CourseWork manage)
target_link_libraries(CourseWork menu)
target_link_libraries(CourseWork sqlwork)
target_link_libraries(CourseWork sqlite)
target_link_libraries(CourseWork sha)