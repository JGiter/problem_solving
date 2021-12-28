cmake_minimum_required(VERSION 3.22)
project(problem_solving VERSION 0.1.0)

add_subdirectory(absolute_permutation)
add_subdirectory(crosses)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
