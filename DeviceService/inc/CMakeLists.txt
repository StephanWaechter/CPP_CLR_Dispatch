set(D "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(${OUTPUT_NAME} PUBLIC 
	${D}/Devices/IDevice.h
	${D}/Devices/Type1Device.h
	${D}/Devices/Type2Device.h
	${D}/DeviceService/Service.h
)