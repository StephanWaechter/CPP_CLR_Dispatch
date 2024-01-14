#pragma once
#include "IDevice.h"

namespace Devices
{

	class Type1Device : public IDevice
	{
	public:
		Type1Device(std::string data) : m_data{ data }
		{}

		std::string Name() const override;
		void Init() override;
		Result Run() override;
		void Terminate() override;

		Serialized Serialize() const override;
		static std::unique_ptr<Type1Device> Deserialize(properties const& map);
	private:
		std::string m_data;
	};
}