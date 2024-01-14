#pragma once
#include "Devices/Serialize.h"
#include "Devices/Type1Device.h"
#include "Devices/Type2Device.h"

namespace Devices
{
	SerializedDeviceList Serialize(IDevice::vector const& devices)
	{
		SerializedDeviceList devicesList;
		devicesList.Version = "V1";
		for (auto& device : devices)
		{
			devicesList.Devices.push_back(
				device->Serialize()
			);
		}
		return devicesList;
	}

	static IDevice::uptr Deserialize(IDevice::Serialized const& device)
	{
		auto& type = device.Type;
		auto& props = device.Props;

		if (type.compare(IDevice::Type1Tag) == 0)
		{
			return Type1Device::Deserialize(props);
		}
		else if (type.compare(IDevice::Type2Tag) == 0)
		{
			return Type2Device::Deserialize(props);
		}
		return {};
	}

	IDevice::vector Deserialize(SerializedDeviceList const& deviceList)
	{
		if (deviceList.Version.compare("V1") != 0)
		{
			throw std::runtime_error("Devices invalid version");
		}

		IDevice::vector devices;
		for (auto& device_data : deviceList.Devices)
		{
			devices.push_back(
				Deserialize(device_data)
			);
		}

		return devices;
	}
}