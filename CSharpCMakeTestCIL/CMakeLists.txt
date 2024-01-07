# CMakeList.txt : CMake project for CSharpCMakeTest2, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(OUTPUT_NAME CSharpCMakeTest2CIL)
add_library (${OUTPUT_NAME} SHARED )
add_subdirectory(inc)
add_subdirectory(src)



target_include_directories(${OUTPUT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

set_target_properties(${OUTPUT_NAME} PROPERTIES COMMON_LANGUAGE_RUNTIME "")
set_target_properties(${OUTPUT_NAME} PROPERTIES DOTNET_TARGET_FRAMEWORK "net7.0")
set_target_properties(${OUTPUT_NAME} PROPERTIES VS_DOTNET_REFERENCES "System")
set_target_properties(${OUTPUT_NAME} PROPERTIES COMPILE_FLAGS "/EHa /Zc:twoPhase-" )

target_link_libraries(${OUTPUT_NAME} PRIVATE NativeLibrary)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${OUTPUT_NAME} PROPERTY CXX_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.
