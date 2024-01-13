#pragma once
#include "nlohmann/json.hpp"
#include "IDevice.h"

#include <vector>
#include <string>

namespace Devices
{
	nlohmann::json Serialize(std::vector<IDevice::uptr> const& devices);
	nlohmann::json Serialize(std::vector<IDevice*> const devices);
	std::vector<IDevice::uptr> Deserilize(nlohmann::json const& json);
}