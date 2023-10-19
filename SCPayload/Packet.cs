using System;

//packatize data based on defined protocol see wiki 
//send 
//recive
//packatize data of image data and telemetry data
namespace SCPayload
{         
	/// <summary>
    /// Packet class will handle data based on defined protocol
    /// </summary>
    public class Packet
	{
        public Packet()
		{
            /// <summary>
            /// Collection of packets that are created after packetization
            /// </summary>
            public byte[][] Packets = { get; private set; }
			private byte packetData;

			/// <summary>
			/// Size of packet
			/// </summary>
			private const int packetSize = 100;

			private const int seqNumFlagSize = sizeof(int);
			private const int endFlagSize = sizeof(bool);
			
			/// <summary>
			/// Defaut constructor
			/// </summary>
			public Packet()
			{ 
			}
			
			/// <summary>
			/// Inits a new instance of Packet with provided data
			/// </summary>
			/// <param name="input">Data to be used for packetization</param>
			public Packet(byte[] input)
			{
				packetData = input;
			}

			/// <summary>
			/// Packetize the data
			/// </summary>
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
			
			/// <summary>
			/// Send data (Stub)
			/// </summary>
			public void Send()
			{
				//Temp send
				Console.WriteLine("Sending the data");
			}
				
			/// <summary>
			/// Recieve data (stub)
			/// </summary>
			public void Recieve()
			{
				//Temp return
				Console.WriteLine("Recieving the data")
			}
		}
	}
}
