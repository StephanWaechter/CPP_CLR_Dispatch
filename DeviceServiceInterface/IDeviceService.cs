using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DeviceServiceInterface
{
    public delegate void DeviceChangeEvent(Device device);
    public delegate void MessageEvent(String device);

    public interface IService
    {
        void Start();
        void Stop();
        bool IsRunning();
        
        event DeviceChangeEvent DeviceUpdatedSignal;
        event MessageEvent ErrorSignal;
        event Action StartSignal;
        event Action StopSignal;
    }
}
