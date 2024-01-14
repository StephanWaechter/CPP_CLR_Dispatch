#pragma once
#include "IDevice.h"
#include <string>
#include <map>
#include <vector>

namespace Devices
{
	struct SerializedDeviceList
	{
		std::string Version;
		std::vector<IDevice::Serialized> Devices;
	};

	SerializedDeviceList Serialize(IDevice::vector const& devices);
	IDevice::vector Deserialize(SerializedDeviceList const& deserializer);
}