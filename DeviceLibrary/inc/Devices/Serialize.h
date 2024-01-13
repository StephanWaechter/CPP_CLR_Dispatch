#pragma once
#include "IDevice.h"
#include "Serialize/Interface.h"
#include "Devices/Type1Device.h"
#include "Devices/Type2Device.h"
#include <optional>

using namespace std::string_literals;

namespace Devices
{
	inline void Serialize(Serialize::Map& seralizer, std::vector<IDevice::uptr> const& devices)
	{
		seralizer.set("Version", "V1"s);
		{
			auto node = seralizer.ListNode("Devices");
			for (auto& device : devices)
			{
				node->emplace_back(*device);
			}
		}
	}

	inline IDevice::uptr DeserializeDevice(Serialize::Deserializer const& node)
	{
		auto type = node.get("Type");
		if (type.compare(Type1Device::Tag) == 0)
		{
			auto device = Type1Device::Deserialize(node);
			return std::make_unique<Type1Device>(device);
		}
		else if(type.compare(Type2Device::Tag) == 0)
		{
			auto device = Type2Device::Deserialize(node);
			return std::make_unique<Type2Device>(node);
		}
	}

	inline std::vector<IDevice::uptr> Deserialize(Serialize::Deserializer const& deserializer)
	{
		std::vector<IDevice::uptr> devices;
		auto version = deserializer.get("Version"s);
		{
			for (auto& node : deserializer.GetElementList("Devices"))
			{
				devices.push_back(
					DeserializeDevice(*node)
				);
			}
		}
	}
}