#include "Devices/IDevice.h"
#include <memory>
#include <vector>
#include <thread>

namespace DeviceService
{
	class Service
	{
	public:
		using pIDevice = std::unique_ptr<Devices::IDevice>;
		template<typename DevcieType, typename... Args>
		void EmplaceDevice(Args... args)
		{
			m_Devices.push_back(
				std::make_unique<DevcieType>(std::forward(args)...)
			);
		};

		void AddDevice(pIDevice device);
		void RemoveDevice(pIDevice device);

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
		std::vector<pIDevice> m_Devices;
	};
}