#include "Devices/Type2Device.h"
#include <iostream>
#include <sstream>

namespace Devices
{
	std::string Type2Device::Name() const
	{
		std::stringstream ss;
		ss << "Type2Device(" << Data << ")";
		return ss.str();
	}

	void Type2Device::Init()
	{
		std::cout << "Init: " << Data << " " << Counter << "\n";
	}

	IDevice::Result Type2Device::Run()
	{
		std::cout << "Run: " << Data << Counter << "\n";
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
		std::cout << "Terminate: " << Data << Counter << "\n";
	}
}