#include "ServiceCLR.h"
#include "Devices/Type1Device.h"
#include "Devices/Type2Device.h"
#include <memory>
using namespace System;
using namespace DeviceServiceInterface;
using namespace System::Windows;

static String^ MarshelValue(std::string const& native)
{
	return System::Runtime::InteropServices::Marshal::PtrToStringAnsi((IntPtr)(char*)native.c_str());
}

static Device^ MarshelValue(Devices::IDevice const& device)
{
	Device^ managed = gcnew Device();
	managed->Name = MarshelValue(device.Name().c_str());
	return managed;
}

namespace DeviceServiceCLR
{
	NativeServiceWrapper::NativeServiceWrapper(ServiceCLR^ managed) : m_managed{ managed }
	{
	}

	void NativeServiceWrapper::OnDeviceUpdate(Devices::IDevice const& device)
	{
		m_managed->OnDeviceUpdate(MarshelValue(device));
	}

	void NativeServiceWrapper::OnError(std::string const& message)
	{
		m_managed->OnError(MarshelValue(message));
	}

	void NativeServiceWrapper::OnStart()
	{
		m_managed->OnStart();
	}

	void NativeServiceWrapper::OnStop()
	{
		m_managed->OnStop();
	}

	ServiceCLR::ServiceCLR()
	{
		m_native = new NativeServiceWrapper(this);
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

	bool ServiceCLR::IsRunning()
	{
		return m_native->IsRunning();
	}
}