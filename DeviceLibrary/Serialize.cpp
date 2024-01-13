#include "Devices/Serialize.h"
#include "Devices/Type1Device.h"
#include "Devices/Type2Device.h"

namespace Devices
{
	using json = nlohmann::json;
	struct JsonData
	{
		std::string Version;
		json Data;
	};

	namespace V1
	{
		constexpr const char* TypeTag = "Type";
		constexpr const char* NameTag = "Name";



		struct DeviceSerializes
		{
			std::string Type;
			std::string Name;
		};

		constexpr const char* Type1DeviceId = "Type1";
		constexpr const char* Type2DeviceId = "Type2";
		IDevice::uptr Desiralize(DeviceSerializes const& datum)
		{
			IDevice::uptr device;
			if (datum.Type.compare(Type1DeviceId) == 0)
			{
				device = std::make_unique<Type1Device>(datum.Name);
			}
			else if (datum.Type.compare(Type2DeviceId) == 0)
			{
				device = std::make_unique<Type2Device>(datum.Name);
			}
			// do nothing for unknown devices for now;
			return device;
		}

		void to_json(json& j, const DeviceSerializes& device) {
			j = json{ {TypeTag, device.Type}, {NameTag, device.Name} };
		}

		void from_json(const json& j, DeviceSerializes& device) {
			j.at(TypeTag).get_to(device.Type);
			j.at(NameTag).get_to(device.Name);
		}

		std::vector<IDevice::uptr> Desiralize(std::vector<DeviceSerializes> const& data)
		{
			std::vector<IDevice::uptr> devices;
			for (auto& datum : data)
			{
				devices.push_back(Desiralize(datum));
			}
			return devices;
		}

		V1::DeviceSerializes Serialize(IDevice const* const datum)
		{
			auto const& serialize_data = datum->Serialize();
			const Type1DeviceData* type1DeviceData = std::any_cast<Type1DeviceData>(&serialize_data);
			if (type1DeviceData != nullptr)
			{
				return V1::DeviceSerializes{
					Type1DeviceId,
					type1DeviceData->Name
				};
			}
			const Type2DeviceData* type2DeviceData = std::any_cast<Type2DeviceData>(&serialize_data);
			if (type2DeviceData != nullptr)
			{
				return V1::DeviceSerializes{
					Type2DeviceId,
					type2DeviceData->Name
				};
			}

			return V1::DeviceSerializes{
				"UNKONW",
				""
			};
		}

		std::vector<V1::DeviceSerializes> Serialize(std::vector<IDevice*> const devices)
		{
			std::vector<V1::DeviceSerializes> data;
			for (auto& device : devices)
			{
				data.push_back(Serialize(device));
			}
			return data;
		}

		std::vector<V1::DeviceSerializes> Serialize(std::vector<IDevice::uptr> const& devices)
		{
			std::vector<V1::DeviceSerializes> data;
			for (auto& device : devices)
			{
				data.push_back(Serialize(device.get()));
			}
			return data;
		}
	}

	nlohmann::json Serialize(std::vector<IDevice::uptr> const& devices)
	{
		nlohmann::json json;
		json["Version"] = "V1";
		json["Data"] = V1::Serialize(devices);
		return json;
	}

	nlohmann::json Serialize(std::vector<IDevice*> const devices)
	{
		nlohmann::json json;
		json["Version"] = "V1";
		json["Data"] = V1::Serialize(devices);
		return json;
	}
	std::vector<IDevice::uptr> Deserilize(nlohmann::json const& json)
	{
		auto version = json.at("Version").get<std::string>();
		if (version.compare("V1") == 0)
		{
			auto data = json.at("Data").get<std::vector<V1::DeviceSerializes>>();
			return V1::Desiralize(data);
		}
		throw std::runtime_error("Unknown version");
	}
}