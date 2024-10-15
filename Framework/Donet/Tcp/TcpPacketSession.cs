﻿using System;

namespace Donet.TCP
{
    public abstract class TCPPacketSession : TCPSession
    {
        public TCPPacketSession(int sendBufferSize = 1024)
        {
            this.sendBufferSize = sendBufferSize;
        }

        private readonly int sendBufferSize;

        public void SendPacket(Packet packet)
        {
            ArraySegment<byte> buffer = SendBuffer.UniqueBuffer.Open(sendBufferSize);
            int size = TCPPacketSerializer.Serialize(buffer, packet);
            buffer = SendBuffer.UniqueBuffer.Close(size);
            Send(buffer);
        }

        public sealed override void OnReceive(ArraySegment<byte> buffer)
        {
            ushort id = PacketFactory.ReadPacketID(buffer);
            Packet packet = PacketFactory.GetPacket(id);
            if (TCPPacketSerializer.Deserialize(buffer, packet))
            {
                packet.OnReceived(this);
                OnPacketReceived(packet);
            }
            else
                Disconnect();
        }

        public abstract void OnPacketReceived(Packet packet);
    }
}
