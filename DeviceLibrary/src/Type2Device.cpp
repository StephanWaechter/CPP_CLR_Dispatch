#include "Devices/Type2Device.h"
#include <iostream>
#include <sstream>

namespace Devices
{
	std::string Type2Device::Name() const
	{
		std::stringstream ss;
		ss << "Type2Device(" << m_data << ")";
		return ss.str();
	}

	void Type2Device::Init()
	{
		std::cout << "Init: " << m_data << " " << Counter << "\n";
	}

	IDevice::Result Type2Device::Run()
	{
		std::cout << "Run: " << m_data << Counter << "\n";
		if (Counter.Tick() == false)
		{
			return {
				false,
				"Counter ran out"
			};
		}
		return { true,{} };
	}

	void Type2Device::Terminate()
	{
		std::cout << "Terminate: " << m_data << Counter << "\n";
	}

	void Type2Device::Serialize(Serialize::Map& serializer) const
	{
		serializer.set("Type", Tag);
		serializer.set("Data", m_data);
	}

	Type2Device Type2Device::Deserialize(Serialize::Deserializer const& deserializer)
	{
		return Type2Device(deserializer.get("Data"));
	}
}