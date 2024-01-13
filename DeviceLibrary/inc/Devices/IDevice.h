#pragma once
#include <string>
#include <memory>
#include <vector>
#include <any>

namespace Devices
{
	class IDevice
	{
	public:
		using uptr = std::unique_ptr<IDevice>;
		struct Result
		{
			bool Success;
			std::string ErrorMessage;
		};
		virtual std::string Name() const = 0;
		virtual void Init() = 0;
		virtual Result Run() = 0;
		virtual void Terminate() = 0;

		virtual std::any Serialize() const = 0;
	};

	inline std::vector<IDevice*> to_ref(std::vector<IDevice::uptr>& devices)
	{
		std::vector<IDevice*> ptr_to;
		for (auto& device : devices)
		{
			ptr_to.push_back(device.get());
		}
		return ptr_to;
	}
}