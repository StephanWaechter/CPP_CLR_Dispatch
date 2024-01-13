// DeviceServiceConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Devices/Type1Device.h>
#include <Devices/Type2Device.h>
#include <Devices/Serialize.h>
#include <DeviceService/Service.h>
#include <thread>

using namespace Devices;
using namespace DeviceService;
using namespace std::chrono_literals;

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

int main()
{
    std::vector<IDevice::uptr> devices;
    devices.push_back(std::make_unique<Type1Device>("Device1"));
    devices.push_back(std::make_unique<Type2Device>("Device2"));
    devices.push_back(std::make_unique<Type2Device>("Device3"));
    
    auto json = Serialize(devices);
    std::cout << json.dump(2) << "\n";

    auto new_devices = Deserilize(json);
    TestService service;
    for (auto& device : new_devices)
    {
        service.AddDevice(
            std::move(device)
        );
    }
    new_devices.clear();

    service.AddDevice(std::make_unique<Type2Device>("Device2"));
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

