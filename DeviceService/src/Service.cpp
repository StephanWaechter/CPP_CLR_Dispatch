#pragma once
#include "DeviceService/Service.h"
#include <vector>
#include <memory>
#include <thread>
#include <chrono>

namespace DeviceService
{
    void Service::AddDevice(pIDevice device)
    {
		m_Devices.push_back(std::move(device));
    }

    void Service::RemoveDevice(pIDevice device)
    {

    }

	void Service::Start()
	{
		using namespace std::chrono_literals;
		Init();
		m_Running = true;
		m_Thread = std::thread(
			[this] 
			{
				while (m_Running)
				{
					Run();
					std::this_thread::sleep_for(1s);
				}
			}
		);	
	}

	void Service::Stop()
	{
		m_Running = false;
		if(m_Running != false)
		{
			m_Thread.join();
		}
	}

	void Service::Init()
	{
		for (auto& d : m_Devices)
		{
			d->Init();
		}
	}

	void Service::Run()
	{
		for (auto& d : m_Devices)
		{
			auto result = d->Run();
			if(!result.Success)
			{
				OnError(result.ErrorMessage);
			}
			else
			{
				OnDeviceUpdate(*d);
			}
		}
	}

	void Service::Terminate()
	{
		for (auto& d : m_Devices)
		{
			d->Terminate();
		}
	}
}