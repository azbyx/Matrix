cmake_minimum_required(VERSION 3.2)

set(NAME_EXECUTABLE "matrix")
set(NAME_TEST "matrix_tests")
set(PATH_HEADERS "headers/")
set(PATH_SRC "sources/")

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 1)
endif()

project(${NAME_EXECUTABLE} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}  LANGUAGES CXX)

exec_program(git ARGS submodule update --init --recursive)
get_filename_component(GTEST_SOURCE ./googletest ABSOLUTE)
add_subdirectory(${GTEST_SOURCE} "googletest")

#message("GTEST_SOURCE - " ${GTEST_SOURCE})

add_executable(${NAME_EXECUTABLE} ${PATH_SRC}main.cpp)

target_include_directories(${NAME_EXECUTABLE} PRIVATE ${PATH_HEADERS})

add_executable(${NAME_TEST} ${PATH_SRC}gtests.cpp)

target_link_libraries(${NAME_TEST} PRIVATE gtest)

target_include_directories(${NAME_TEST} PRIVATE ${PATH_HEADERS})

set_target_properties(${NAME_EXECUTABLE} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(${NAME_TEST} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(${NAME_EXECUTABLE} PRIVATE /W4)
    target_compile_options(${NAME_TEST} PRIVATE /W4)
else()
    target_compile_options(${NAME_EXECUTABLE} PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(${NAME_TEST} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS ${NAME_EXECUTABLE} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT azbyx@inbox.ru)

include(CPack)
enable_testing()
add_test(${NAME_TEST} ${NAME_TEST})
