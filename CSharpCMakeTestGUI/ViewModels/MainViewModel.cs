using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Collections;
using CommunityToolkit.Mvvm.Input;
using DeviceServiceInterface;
using System.Collections.ObjectModel;
using System.Windows;

namespace CSharpCMakeTestGUI.ViewModels
{
    partial class MainViewModel : ObservableObject
    {
        public MainViewModel(IService service)
        {
            Service = service;
            Service.DeviceUpdatedSignal += OnDeviceUpdated;
            Service.ErrorSignal += OnError;

            StartCommand = new RelayCommand(OnStartCommand);
            StopCommand = new RelayCommand(OnStopCommand);
        }

        public ObservableCollection<String> Message { get; } = new();

        public IRelayCommand StartCommand { get; }
        private void OnStartCommand()
        {
            Service.Start();
        }

        public IRelayCommand StopCommand { get; }
        private void OnStopCommand()
        {
            Service.Stop();
        }
        private void OnError(String message)
        {
            Message.Add(message);
        }

        private void OnDeviceUpdated(Device device)
        {
            Message.Add(device.Name);
        }



        public IService Service { get; }
    }
}
