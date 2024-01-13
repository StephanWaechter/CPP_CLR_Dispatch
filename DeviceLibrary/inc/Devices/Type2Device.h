#pragma once
#include "IDevice.h"
#include <string>
#include <iostream>

namespace Devices
{
	struct Type2DeviceData
	{
		std::string Name;
	};

	class Type2Device : public IDevice
	{
		class Counter
		{
		public:
			using Type = unsigned int;
			Counter(Type max) : Max{max}, Current{max}
			{}

			bool Tick()
			{
				Current--;
				if (Current == 0)
				{
					Current = Max;
					return true;
				}
				return false;
			}

			friend static std::ostream& operator<<(std::ostream& os, Counter const& counter)
			{
				os << "(" << counter.Current << "\\" << counter.Max << ")";
				return os;
			}

		private:
			Type Max{ 1 };
			Type Current{ 0 };
		};

	public:
		Type2Device(std::string data) : m_data{ data }
		{}

		std::string Name() const override;
		void Init() override;
		Result Run() override;
		void Terminate() override;

		static constexpr const char* Tag = "Type2Device";
		void Serialize(Serialize::Map& serializer) const override;
		static Type2Device Deserialize(Serialize::Deserializer const& deserializer);
	private:
		std::string m_data;
		Counter Counter{3};
	};
}