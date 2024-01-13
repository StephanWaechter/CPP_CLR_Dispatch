#pragma once
#include "IDevice.h"
#include <string>

namespace Devices
{
	struct Type1DeviceData
	{
		std::string Name;
	};

	class Type1Device : public IDevice
	{
	public:
		Type1Device(std::string data) : m_data{ data }
		{}

		std::string Name() const override;
		void Init() override;
		Result Run() override;
		void Terminate() override;

		std::any Serialize() const override;
	private:
		std::string m_data;
	};
}