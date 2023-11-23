#include "Packet.h"
#include "json.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Packet::Packet() 
{

}

Packet::Packet(const std::vector<unsigned char>& inputData, const std::string& destID, const std::string& srcID, Telem data)
              : packetData(inputData), destinationID(destID), sourceID(srcID), telemetryData(data)
{

}

void Packet::Packetize()
{
	if (!telemetryData.isValid())
	{
		string response = telemetryData.errorResponse("DATA REJECTION", "Invalid telemetry data");
		//Finish handling
		cout << response << endl;
		return;
	}
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
		packetJSON["data"]["Telemetry"]["Longitude"] = telemetryData.getLong();
		packetJSON["data"]["Telemetry"]["Latitude"] = telemetryData.getLat();
		packetJSON["data"]["Telemetry"]["Time"] = telemetryData.getTime();
		packetJSON["data"]["isLastPacket"] = (i == totalPackets - 1);
		Packets.push_back(packetJSON);
	}
}

void Packet::Send()
{
	std::cout << "Sending data" << std::endl;
}

void Packet::Recieve()
{
	std::cout << "Receiving the data" << std::endl;
}

string Packet::getIP(int servicenum)
{
	return IP[servicenum];
}

void Packet::readIP()
{
    ifstream file("../IP.txt");
    if (file.is_open()) {
        for (int i = 0; i < 7; i++)
        {
            getline(file, IP[i]);
        }
        file.close();
    }
}