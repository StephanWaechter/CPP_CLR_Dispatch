#pragma once
#include <NativeLibrary/DeviceObserver.h>
#include <vcclr.h>

using namespace CSharpCMakeTestLibrary;

namespace CSharpCMakeTestCIL
{
	struct NativeObserver : public NativeLibrary::DeviceObserver
	{
		NativeObserver(CSharpCMakeTestLibrary::IObserver^ managed) : m_managed{ managed } {}
		void OnDeviceUpdate(NativeLibrary::Device const& device) override;
		void OnError(std::string const& message) override;

		gcroot<NativeLibrary::DeviceObserver^> m_managed;
	};

	public ref class Observer : public CSharpCMakeTestLibrary::IObserver
	{
	public:
		virtual event CSharpCMakeTestLibrary::DeviceUpdateEvent^ DeviceUpdateNotifier;
		virtual event CSharpCMakeTestLibrary::DeviceUpdateEvent^ ErrorNotifier;
	
	internal:
		void OnDeviceUpdate(System::String^ string)
		{
			DeviceUpdateNotifier(string);
		}

		void OnError(System::String^ string)
		{
			ErrorNotifier(string);
		}

		~Observer()
		{
			this->!Observer();
		}

		!Observer()
		{
			delete(m_native);
		}

		NativeObserver& Native()
		{
			return *m_native;
		}

	private:
		CommunityToolkit::Mvvm::Messaging::IMessenger^ m_messenger;
		NativeObserver* m_native{ nullptr };

		// Inherited via IObserver

	};
}