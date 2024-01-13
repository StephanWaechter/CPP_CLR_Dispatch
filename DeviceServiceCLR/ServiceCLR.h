#pragma once
#include "DeviceService/Service.h"
#include "Devices/Type1Device.h"
#include "Devices/Type2Device.h"
#include <string>
#include <vcclr.h>

namespace DeviceServiceCLR
{
	ref class ServiceCLR;
	class NativeServiceWrapper : public DeviceService::Service
	{
	public:
		NativeServiceWrapper(ServiceCLR^ managed);

	protected:
		void OnDeviceUpdate(Devices::IDevice const& device) override;
		void OnError(std::string const& message) override;
		void OnStart() override;
		void OnStop() override;

	private:
		gcroot<ServiceCLR^> m_managed;
	};

	public ref class ServiceCLR abstract
	{

	public:
		ServiceCLR();

		virtual void Start();
		virtual void Stop();
		virtual bool IsRunning();

		virtual void OnDeviceUpdate(DeviceServiceInterface::Device^ device) = 0;
		virtual void OnError(System::String^ device) = 0;
		virtual void OnStart() = 0;
		virtual void OnStop() = 0;

	private:
		NativeServiceWrapper* m_native{ nullptr };
	};



};