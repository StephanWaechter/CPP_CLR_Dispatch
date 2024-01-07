set(D "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(${OUTPUT_NAME} PUBLIC
	${D}/Service.cpp
	${D}/Type1Device.cpp
	${D}/Type2Device.cpp
)
