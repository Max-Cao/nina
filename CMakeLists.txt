cmake_minimum_required(VERSION 3.10.0)
project(nina VERSION 0.1.0 LANGUAGES C CXX)

add_library(nina src/nina.h)

target_include_directories(nina PUBLIC src/nina.h)

# need fmt
include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        12.1.0)
FetchContent_MakeAvailable(fmt)

target_compile_features(fmt PRIVATE cxx_std_26)
target_link_libraries(nina PRIVATE fmt::fmt)

message("-- u can use **nina** now --")