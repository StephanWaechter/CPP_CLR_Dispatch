#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>
namespace Devices
{
	class IDevice
	{
	public:
		using uptr = std::unique_ptr<IDevice>;
		using vector = std::vector<uptr>;
		using properties = std::map<std::string, std::string>;
		static constexpr char const* Type1Tag = "Type1";
		static constexpr char const* Type2Tag = "Type2";

		struct Serialized
		{
			std::string Type;
			properties Props;
		};

		struct Result
		{
			bool Success;
			std::string ErrorMessage;
		};
		virtual std::string Name() const = 0;
		virtual void Init() = 0;
		virtual Result Run() = 0;
		virtual void Terminate() = 0;

		virtual Serialized Serialize() const = 0;
	};
}