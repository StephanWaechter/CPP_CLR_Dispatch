#pragma once
#include <Serialize/Interface.h>
#include <string>
#include <memory>
#include <vector>
#include <any>

namespace Devices
{
	class IDevice : public Serialize::Serializable
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
	};
}