#include "ServiceCLR.h"
#include "Devices/Type1Device.h"
#include "Devices/Type2Device.h"
#include <memory>

namespace DeviceServiceCLR
{
	ServiceCLR::ServiceCLR()
	{
		m_native = new NativeService(this);
		m_native->AddDevice(std::make_unique<Devices::Type1Device>("Device1"));
		m_native->AddDevice(std::make_unique<Devices::Type2Device>("Device2"));
	}

	void ServiceCLR::Start()
	{
		m_native->Start();
	}

	void ServiceCLR::Stop()
	{
		m_native->Stop();
	}
}