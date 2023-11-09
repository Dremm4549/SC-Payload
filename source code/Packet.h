#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;
/// <summary>
/// Packet class will handle data based on defined protocol
/// </summary>
class Packet
{
private:
	std::vector<unsigned char> packetData;
	static const int packetSize = 100;
	static const int seqNumFlagSize = sizeof(int);
	static const int endFlagSize = sizeof(int);
	string IP[7];
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
	string getIP(int servicenum)
	{
		return IP[servicenum];
	}
	void readIP();
};