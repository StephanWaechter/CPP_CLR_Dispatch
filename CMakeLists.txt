# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("CSharpCMakeTest2" LANGUAGES CXX CSharp)

if(NOT MSVC)
    message(FATAL_ERROR "This CMake files only works with MSVC.")
endif(NOT MSVC)

# Include sub-projects.
add_subdirectory ("NativeLibrary")
add_subdirectory ("CSharpCMakeTest2CIL")

