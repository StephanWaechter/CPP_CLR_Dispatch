#pragma once
#include "IDevice.h"
#include <string>

namespace Devices
{
	class Type1Device : public IDevice
	{
	public:
		Type1Device(std::string data) : Data{ data }
		{}
		std::string Name() const override;
		void Init() override;
		Result Run() override;
		void Terminate() override;

	private:
		std::string Data;
	};

}