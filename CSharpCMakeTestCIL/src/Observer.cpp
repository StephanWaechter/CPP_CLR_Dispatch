#pragma once
#include <CSharpCMakeTestCIL/Observer.h>

static System::String^ ToString(std::string const& string)
{
	return System::Runtime::InteropServices::Marshal::PtrToStringAnsi((System::IntPtr)(char*)string.c_str());
}

namespace CSharpCMakeTestCIL
{
	void NativeObserver::OnDeviceUpdate(NativeLibrary::Device const& device)
	{
		m_managed->OnDeviceUpdate(
			ToString(device.Name())
		);
	}

	void NativeObserver::OnError(std::string const& message)
	{
		m_managed->OnError(
			ToString(message)
		);
	}
}