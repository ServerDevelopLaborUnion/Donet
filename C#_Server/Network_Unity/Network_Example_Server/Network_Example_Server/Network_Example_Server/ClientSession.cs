﻿using Donet;
using System.Net;

namespace Network_Example_Server
{
    public class ClientSession : PacketSession
    {
        public override void OnConnected(EndPoint endPoint)
        {
        }

        public override void OnDisconnected(EndPoint endPoint)
        {
        }

        public override void OnPacketReceived(Packet packet)
        {
        }

        public override void OnSend(int transferred)
        {
        }
    }
}
