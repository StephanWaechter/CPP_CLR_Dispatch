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

namespace CSharpCMakeTestGUI.ViewModels
{
    partial class MainViewModel : ObservableObject
    {
        public IService Service { get; }
        public MainViewModel(IService service)
        {
            Service = service;
            Service.DeviceUpdatedSignal += OnDeviceUpdated;
            Service.ErrorSignal += OnError;
            Service.StartSignal += OnStart;
            Service.StopSignal += OnStop;

            StartCommand = new RelayCommand(OnStartCommand);
            StopCommand = new RelayCommand(OnStopCommand);

            UpdateRunning();
        }

        [ObservableProperty]
        bool isRunning;

        [ObservableProperty]
        bool isNotRunning;

        private void OnStart()
        {
            Message.Add("Start");
            UpdateRunning();
        }

        private void OnStop()
        {
            Message.Add("Stop");
            UpdateRunning();
        }

        private void UpdateRunning()
        {
            IsRunning = Service.IsRunning();
            IsNotRunning = !Service.IsRunning();
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
    }
}
