﻿using ServerCore;
using System.Net;

namespace DummyClient
{
    public class ServerSession : PacketSession
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