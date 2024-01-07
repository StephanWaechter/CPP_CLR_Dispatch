#include "DeviceService/Service.h"
#include "Devices/Type1Device.h"
#include "Devices/Type2Device.h"
#include <thread>
using namespace DeviceService;
using namespace Devices;
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
    };
}

int main(int argc, char** argv)
{
    TestService manager;
    manager.AddDevice(std::make_unique<Type1Device>("Device1"));
    manager.AddDevice(std::make_unique<Type2Device>("Device2"));
    std::cout << "Start\n";
    manager.Start();
    std::this_thread::sleep_for(5s);
    manager.Stop();
    std::cout << "Stop\n";
}
