#include "Devices/Type1Device.h"
#include <iostream>
#include <sstream>
namespace Devices
{
	std::string Type1Device::Name() const
	{
		std::stringstream ss;
		ss << "Type1Device(" << Data << ")";
		return ss.str();
	}

	void Type1Device::Init()
	{
		std::cout << "Init: " << Data << "\n";
	}

	IDevice::Result Type1Device::Run()
	{
		if (Data.empty())
		{
			return { false,"Data was empty" };
		};
		std::cout << "Run: " << Data << "\n";
		return { true,{} };
	}

	void Type1Device::Terminate()
	{
		std::cout << "Terminate: " << Data << "\n";
	}
}