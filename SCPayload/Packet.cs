using System;

//packatize data based on defined protocol see wiki 
//send 
//recive
//packatize data of image data and telemetry data
namespace SCPayload
{ 
	private class Packet
	{
		public Packet()
		{
			public byte[][] Packets = { get; private set; }
			private byte packetData;
			private const int packetSize = 100;

			private const int seqNumFlagSize = sizeof(int);
			private const int endFlagSize = sizeof(bool);
			
			//Inintialize packetData
			public Packet(byte[] input)
			{
				packetData = input;
			}

			//Packetize the data
			public void Packetize()
			{
				int realPacketSize = packetSize - seqNumSize - endFlagSize;
				//Find total number of packets using data length
				int totalPackets = (int)Math.Celing((double)packetData.Length / packetSize);
				Packets = new byte[totalPackets][];
				//Create the packet
				for (int i = 0; i < totalPackets; i++) 
				{
					bool isLastPacket = i == totalPackets - 1;
					//Get size of packet
					//If the data is not a multiple of realPacketSize
					int currentSize = (i == totalPackets - 1 && packetData.Length % realPacketSize != 0)
											? packetData.Length % realPacketSize;
											: realPacketSize;
					int totalCurrentPacketSize = currentSize + seqNumberSize + endFlagSize;

					//Make space for packet and copy data into it
					Packets[i] = new byte[currentSize];
					Array.Copy(packetData, i * packetSize, Packets[i], 0, currentSize);
					
				}
			}	
			
			//Send stub
			public void Send()
			{
				//Temp send
				Console.WriteLine("Sending the data");
			}
				
			//Recieve stub
			public void Recieve()
			{
				//Temp return
				Console.WriteLine("Recieving the data")
			}
		}
	}
}
