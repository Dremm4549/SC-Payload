#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <>

/// <summary>
/// Packet class will handle data based on defined protocol
/// </summary>
class Packet
{
private:
	std::vector<unsigned char> packetData;
	static const int packetSize = 66560;
	static const int seqNumFlagSize = sizeof(int);
	static const int endFlagSize = sizeof(int);
public:
	std::vector<std::vector<unsigned char>> Packets;
	/// <summary>
	/// Default constructor for packet
	/// </summary>
	Packet() {}
	/// <summary>
	/// Creates new instance of packet with data
	/// </summary>
	/// <param name="inputData">Data to be used for packetization</param>
	Packet(const std::vector<unsigned char>& inputData) : packetData(inputData) {}
	/// <summary>
	/// Packetize the data
	/// </summary>
	void Packetize()
	{
		int realPacketSize = packetSize - seqNumFlagSize - endFlagSize;
		int totalPackets = (packetData.size() + realPacketSize - 1) / realPacketSize;

		Packets.clear();
		Packets.resize(totalPackets);

		for (int i = 0; i < totalPackets; i++)
		{
			int start = i * realPacketSize;
			int end = std::min(start + realPacketSize, static_cast<int>(packetData.size()));
			std::vector<unsigned char> thisPacket(seqNumFlagSize + endFlagSize + (end - start));
			int seqNum = i;
			bool endFlag = (i == totalPackets - 1);
			memcpy(thisPacket.data(), &seqNum, seqNumFlagSize);
			memcpy(thisPacket.data() + seqNumFlagSize, &endFlag, endFlagSize);
			std::copy(packetData.begin() + start, packetData.begin() + end, thisPacket.begin() + seqNumFlagSize + endFlagSize);
			Packets.push_back(thisPacket);
		}
	}
	/// <summary>
	/// Send data (Stub)
	/// </summary>
	void Send()
	{
		std::cout << "Sending data" << std::endl;
	}
	/// <summary>
	/// Recieve data (stub)
	/// </summary>
	void Recieve()
	{
		std::cout << "Receiving the data" << std::endl;
	}
};