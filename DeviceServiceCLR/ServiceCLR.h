#pragma once
#include "DeviceService/Service.h"
#include <string>
#include <vcclr.h>

namespace DeviceServiceCLR
{
	using namespace System;
	using namespace DeviceServiceInterface;
	using namespace System::Windows;

	static String^ MarshelString(std::string const& native)
	{
		return System::Runtime::InteropServices::Marshal::PtrToStringAnsi((IntPtr)(char*)native.c_str());
	}

	static Device^ MarshelDevice(Devices::IDevice const& device)
	{
		Device^ managed = gcnew Device();
		managed->Name = MarshelString(device.Name().c_str());
		return managed;
	}

	class NativeService;
	public ref class ServiceCLR : public DeviceServiceInterface::IService
	{
	public:
		ServiceCLR();

		// Inherited via IService
		virtual event DeviceChangeEvent^ DeviceUpdatedSignal;
		virtual event MessageEvent^ ErrorSignal;
		virtual event Action^ StartSignal;
		virtual event Action^ StopSignal;

		virtual void Start();
		virtual void Stop();
		virtual bool IsRunning();

	internal:
		void OnDeviceUpdate(Devices::IDevice const& device)
		{
			DeviceUpdatedSignal(
				MarshelDevice(device)
			);
		}

		void OnError(std::string const& message)
		{
			ErrorSignal(
				MarshelString(message)
			);
		}

		void OnStart()
		{
			StartSignal();
		}

		void OnStop()
		{
			StopSignal();
		}

	private:
		NativeService* m_native;


	};

	class NativeService : public DeviceService::Service
	{
	public:
		NativeService(ServiceCLR^ managed) : m_managed{ managed }
		{
		}

	protected:
		virtual void OnDeviceUpdate(Devices::IDevice const& device)
		{
			m_managed->OnDeviceUpdate(device);
		}

		virtual void OnError(std::string const& message)
		{
			m_managed->OnError(message);
		}

		virtual void OnStart()
		{
			m_managed->OnStart();
		}

		virtual void OnStop()
		{
			m_managed->OnStop();
		}

	private:
		gcroot<ServiceCLR^> m_managed;
	};
};