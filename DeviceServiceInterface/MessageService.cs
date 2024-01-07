using CommunityToolkit.Mvvm.Messaging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DeviceServiceInterface
{
    record ErrorMessage(String Message);
    record DeviceUpdatedMessage(Device device);

    record StartMessage();
    record StopMessage();

    internal class MessageService
    {
        private readonly IMessenger messenger;
        private readonly IService service;

        public MessageService(IMessenger _messenger, IService _service)
        {
            messenger = _messenger;
            service = _service;
            service.DeviceUpdatedSignal += Service_DeviceUpdatedSignal;
            service.ErrorSignal += Service_ErrorSignal;
        }

        public void Start()
        {
            messenger.Send<StartMessage>();
            service.Start();
        }

        public void Stop()
        {
            messenger.Send<StopMessage>();
            service.Stop();
        }

        private void Service_ErrorSignal(string device)
        {
            messenger.Send<ErrorMessage>(new(device));
        }

        private void Service_DeviceUpdatedSignal(Device device)
        {
            messenger.Send<DeviceUpdatedMessage>(new(device);
        }
    }
}
