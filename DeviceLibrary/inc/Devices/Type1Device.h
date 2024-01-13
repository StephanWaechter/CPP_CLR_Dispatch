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

		static constexpr const char* Tag = "Type1Device";
		void Serialize(Serialize::Map& serializer) const override;
		static Type1Device Deserialize(Serialize::Deserializer const& deserializer);
	private:
		std::string m_data;
	};
}