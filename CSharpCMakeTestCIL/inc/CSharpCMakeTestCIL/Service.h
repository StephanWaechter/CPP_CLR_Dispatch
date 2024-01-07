#pragma once
#include "Observer.h"
#include <NativeLibrary/DeviceManager.h>
#include <NativeLibrary/Type1Device.h>
#include <NativeLibrary/Type2Device.h>



using namespace System;

namespace CSharpCMakeTestCIL
{
	public ref class Service : public CSharpCMakeTestLibrary::IService
	{
	public:
		Service(Observer^ observer) : m_observer(observer)
		{
			m_native = new NativeLibrary::DeviceManager(observer->Native());
			m_native->AddDevice(new NativeLibrary::Type1Device("Device1"));
			m_native->AddDevice(new NativeLibrary::Type2Device("Device2"));
		}

		~Service()
		{
			this->!Service();
		}

		!Service()
		{
			delete(m_native);
		}

		void Start()
		{
			m_native->Start();
		}

		void Stop()
		{
			m_native->Stop();
		}

		virtual property CSharpCMakeTestLibrary::IObserver^ GetObserver
		{
			CSharpCMakeTestLibrary::IObserver^ get()
			{
				return m_observer;
			}
		}

	private:
		Observer^ m_observer;
		NativeLibrary::DeviceManager* m_native;
	};
}