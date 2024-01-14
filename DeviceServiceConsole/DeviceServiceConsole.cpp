// DeviceServiceConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Devices/Type1Device.h>
#include <Devices/Type2Device.h>
#include <Devices/Serialize.h>
#include <DeviceService/Service.h>
#include <nlohmann/json.hpp>

#include <thread>

using namespace Devices;
using namespace DeviceService;
using namespace std::chrono_literals;

using json = nlohmann::json;

namespace
{
    struct TestService : public Service
    {
        void OnDeviceUpdate(IDevice const& device)
        {
            std::cout << device.Name() << "\n";
        }
        void OnError(std::string const& message)
        {
            std::cout << message << "\n";
        }
        void OnStart()
        {
            std::cout << "Start\n";
        }
        void OnStop()
        {
            std::cout << "Stop\n";
        }
    };
}

namespace Devices
{
    void to_json(json& j, const IDevice::Serialized& d) {
        j = json{ {"Type", d.Type}, {"Props", d.Props} };
    }

    void from_json(const json& j, IDevice::Serialized& d) {
        j.at("Type").get_to(d.Type);
        j.at("Props").get_to(d.Props);
    }

    void to_json(json& j, const SerializedDeviceList& d) {
        j = json{ {"Version", d.Version}, {"Devices", d.Devices} };
    }

    void from_json(const json& j, SerializedDeviceList& d) {
        j.at("Version").get_to(d.Version);
        j.at("Devices").get_to(d.Devices);
    }
}

int main()
{
    IDevice::vector devices;
    devices.push_back(std::make_unique<Type1Device>("Device1"));
    devices.push_back(std::make_unique<Type2Device>("Device2"));
    devices.push_back(std::make_unique<Type2Device>("Device3"));    

    auto serializedData = Devices::Serialize(devices);
    json js = serializedData;

    std::cout << js.dump(2) << "\n";
    
    TestService service;
    auto deserializedData = js.get<SerializedDeviceList>();
    for (auto& device : Devices::Deserialize(deserializedData))
    {
        service.AddDevice(
            std::move(device)
        );
    }

    service.Start();
    std::this_thread::sleep_for(5s);
    service.Stop();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

