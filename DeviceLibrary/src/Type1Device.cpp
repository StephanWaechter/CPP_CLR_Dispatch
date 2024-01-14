#include "Devices/Type1Device.h"
#include "Devices/Serialize.h"

#include <iostream>
#include <sstream>
namespace Devices
{
	std::string Type1Device::Name() const
	{
		std::stringstream ss;
		ss << "Type1Device(" << m_data << ")";
		return ss.str();
	}

	void Type1Device::Init()
	{
		std::cout << "Init: " << m_data << "\n";
	}

	IDevice::Result Type1Device::Run()
	{
		if (m_data.empty())
		{
			return { false,"Data was empty" };
		};
		std::cout << "Run: " << m_data << "\n";
		return { true,{} };
	}

	void Type1Device::Terminate()
	{
		std::cout << "Terminate: " << m_data << "\n";
	}

	IDevice::Serialized Type1Device::Serialize() const
	{
		Serialized device;
		device.Type = Type1Tag;
		device.Props["Data"] = m_data;
		return device;
	}

	std::unique_ptr<Type1Device> Type1Device::Deserialize(properties const& props)
	{
		if (auto data = props.find("Data"); data != props.end())
		{
			std::string d = props.at("Data");
			return std::make_unique<Type1Device>(d);
		}
		return nullptr;
	}
}