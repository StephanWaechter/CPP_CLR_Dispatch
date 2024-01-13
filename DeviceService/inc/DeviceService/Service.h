#include "Devices/IDevice.h"
#include <memory>
#include <vector>
#include <thread>

namespace DeviceService
{
	class Service
	{
	public:
		template<typename DevcieType, typename... Args>
		void EmplaceDevice(Args... args)
		{
			m_Devices.push_back(
				std::make_unique<DevcieType>(std::forward(args)...)
			);
		};

		void AddDevice(Devices::IDevice::uptr device);
		void RemoveDevice(Devices::IDevice::uptr device);

		void Start();
		void Stop();
		bool IsRunning() const;

	protected:
		virtual void OnStart() = 0;
		virtual void OnStop() = 0;
		virtual void OnDeviceUpdate(Devices::IDevice const& device) = 0;
		virtual void OnError(std::string const& message) = 0;

	private:
		void Init();
		void Run();
		void Terminate();

		bool m_Running{false};
		std::thread m_Thread;
		std::vector<Devices::IDevice::uptr> m_Devices;
	};
}