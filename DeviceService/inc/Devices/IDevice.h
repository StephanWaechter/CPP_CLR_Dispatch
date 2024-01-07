#pragma once
#include <string>
namespace Devices
{
	class IDevice
	{
	public:
		struct Result
		{
			bool Success;
			std::string ErrorMessage;
		};
		virtual std::string Name() const = 0 ;
		virtual void Init() = 0;
		virtual Result Run() = 0;
		virtual void Terminate() = 0;
	};
}