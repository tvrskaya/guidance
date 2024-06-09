cmake_minimum_required(VERSION 3.20)
project(BigInt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/lib/googletest")
set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/googletest/include")

set(PROJECT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include" )

add_subdirectory(${GTEST_ROOT})

function(remove_file_if_exists FILE_PATH)
    if(EXISTS ${FILE_PATH})
        file(REMOVE ${FILE_PATH})
    endif()
endfunction()

function(create_target_directory PROJECT_TARGET_DIRECTORY)
    if(NOT EXISTS ${PROJECT_TARGET_DIRECTORY})
        file(MAKE_DIRECTORY ${PROJECT_TARGET_DIRECTORY})
    endif()
endfunction()

set(PROJECT_TARGET_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/target")
create_target_directory(${PROJECT_TARGET_DIRECTORY})

enable_testing()
add_subdirectory(test)