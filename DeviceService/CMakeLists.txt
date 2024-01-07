# CMakeList.txt : CMake project for CSharpCMakeTest2, include source and define
# project specific logic here.
#
project(DeviceService)
cmake_minimum_required(VERSION 3.24)

# Add source to this project's executable.
set(OUTPUT_NAME DeviceService)
add_library (${OUTPUT_NAME})

target_include_directories(${OUTPUT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${OUTPUT_NAME} PROPERTY CXX_STANDARD 20)
endif()

add_executable(TestDeviceService TestDeviceService.cpp)
target_link_libraries(TestDeviceService PRIVATE ${OUTPUT_NAME})

add_subdirectory(inc)
add_subdirectory(src)

# TODO: Add tests and install targets if needed.
