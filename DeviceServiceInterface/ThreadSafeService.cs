using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DeviceServiceInterface
{
    public class ThreadSafeService : IService
    {
        public ThreadSafeService(Action<Action> _dispatcher, IService _service) 
        {
            dispatcher = _dispatcher;
            service = _service;
            service.DeviceUpdatedSignal += Service_DeviceUpdatedSignal;
            service.ErrorSignal += Service_ErrorSignal;
        }

        private void Service_DeviceUpdatedSignal(Device device)
        {
            dispatcher.Invoke(
                () => { DeviceUpdatedSignal.Invoke(device); }
            );
        }

        private void Service_ErrorSignal(String message)
        {
            dispatcher.Invoke(
                () => { ErrorSignal.Invoke(message); }
            );
        }

        private readonly Action<Action> dispatcher;
        private readonly IService service;

        public event DeviceChangeEvent DeviceUpdatedSignal = null!;
        public event MessageEvent ErrorSignal = null!;

        public void Start()
        {
            service.Start();
        }

        public void Stop()
        {
            service.Stop();
        }
    }
}
