#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <json.hpp>

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
	std::string destinationID;
	std::string sourceID;
public:
	std::vector<nlohmann::json> Packets;
	/// <summary>
	/// Default constructor for packet
	/// </summary>
	Packet() {}
	/// <summary>
	/// Creates new instance of packet with data
	/// </summary>
	/// <param name="inputData">Data to be used for packetization</param>
	Packet(const std::vector<unsigned char>& inputData, const std::string& destID, const std::string& srcID) 
		: packetData(inputData), destinationID(destID), sourceID(srcID) {}
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
			nlohmann::json packetJSON;
			packetJSON["numPacketsExpected"] = totalPackets;
			packetJSON["data"]["Sequence Number"] = i;
			packetJSON["data"]["message"] = std::vector<unsigned char>(packetData.begin() + start, packetData.begin() + end);
			packetJSON["destination"] = destinationID;
			packetJSON["source"] = sourceID;
			packetJSON["data"]["isLastPacket"] = (i == totalPackets - 1);
			Packets.push_back(packetJSON);
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