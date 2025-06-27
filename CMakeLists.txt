cmake_minimum_required(VERSION 3.10)

project(MODELS_LIB VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(MODELS_LIB main.cpp)
set_target_properties(MODELS_LIB PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(unitTest UNIT_TESTS/test.cpp)
target_link_libraries(unitTest PRIVATE Catch2::Catch2WithMain)
set_target_properties(unitTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")