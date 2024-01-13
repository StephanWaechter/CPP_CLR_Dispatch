#include "Devices/Type1Device.h"
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

	std::any Type1Device::Serialize() const
	{
		return Type1DeviceData{ m_data };
	}
}