#pragma once
#include "IDevice.h"
#include <string>
#include <iostream>

namespace Devices
{
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
		Type2Device(std::string data) : Data{ data }
		{}

		std::string Name() const override;
		void Init() override;
		Result Run() override;
		void Terminate() override;

	private:
		std::string Data;
		Counter Counter{3};
	};
}