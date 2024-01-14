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

	IDevice::Serialized Type2Device::Serialize() const
	{
		Serialized data;
		data.Type = Type2Tag;
		data.Props["Data"] = m_data;
		return data;
	}

	std::unique_ptr<Type2Device> Type2Device::Deserialize(properties const& props)
	{
		if (auto data = props.find("Data"); data != props.end())
		{
			std::string d = props.at("Data");
			return std::make_unique<Type2Device>(d);
		}
		return nullptr;	
	}
}