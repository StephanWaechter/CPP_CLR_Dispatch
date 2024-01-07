using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DeviceServiceInterface
{
    public interface IDeviceServiceWrapper
    {
        void Start();
        void Stop();
        bool IsRunning();

        void OnStart();
        void OnStop();
        void OnDeviceUpdate(Device device);
        void OnError(String message);
    }
}
