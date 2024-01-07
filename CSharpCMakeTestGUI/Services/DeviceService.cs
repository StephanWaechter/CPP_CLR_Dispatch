using DeviceServiceInterface;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace CSharpCMakeTestGUI.Services
{
    internal class DeviceService : DeviceServiceCLR.ServiceCLR, DeviceServiceInterface.IService
    {
        public event DeviceChangeEvent DeviceUpdatedSignal = null!;
        public event MessageEvent ErrorSignal = null!;
        public event Action StartSignal = null!;
        public event Action StopSignal = null!;

        private static void Dispatch(Action action)
        {
            Application.Current.Dispatcher.BeginInvoke(action);
        }

        public override void OnDeviceUpdate(Device device)
        {
            Dispatch(() => DeviceUpdatedSignal.Invoke(device));
        }

        public override void OnError(string message)
        {
            Dispatch(() => ErrorSignal.Invoke(message));
        }

        public override void OnStart()
        {
            Dispatch(() => StartSignal.Invoke());
        }

        public override void OnStop()
        {
            Dispatch(() => StopSignal.Invoke());
        }
    }
}
