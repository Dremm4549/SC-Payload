#include "Packet.h"
#include "json.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Packet::Packet() 
{

}

Packet::Packet(const std::vector<unsigned char>& inputData, const std::string& destID, const std::string& srcID)
              : packetData(inputData), destinationID(destID), sourceID(srcID) 
{

}

void Packet::Packetize()
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
    ifstream ipconfig("../IP.txt");
   	std::string line;
	
	if (!ipconfig.is_open()) 
	{
		return;	
	}

	while (getline(ipconfig, line)) 
		{
			std::istringstream ss(line);
			std::string token;
			std::string ip;
			int counter = 0;

			while (std::getline(ss, token, ',')) 
			{
				counter++;
				if (counter == 2) 
				{
					int key = std::stoi(token);
					serviceDictionary.insert(pair<int, std::string>(key, ip));
				}
				else 
				{
					ip = token;
				}			
			}
		}

		ipconfig.close();
}

void Packet::PrintIp(){
	for(const auto& entry : serviceDictionary){
		std::cout << "Service ID: " << entry.first << std::endl;
	}

}

bool Packet::FindService(int serviceKey)
{
	// PrintIp();

	 if(serviceDictionary.find(serviceKey)!=serviceDictionary.end()){
      //if the element is found before the end of the map
	  return true;
      //if the element is present then you can access it using the index
    }
	else
	{
		return false;
	}
	// std::string key = "5";
	// if (serviceDictionary.find(5) != serviceDictionary.end()) {
    //     std::cout << "Key " << key << " exists in the map." << std::endl;
    // } else {
    //     std::cout << "Key " << key << " does not exist in the map." << std::endl;
    // }
}

std::string Packet::GetServiceIP(int serviceID)
{
	 std::string serviceIp = serviceDictionary[serviceID];
	 return serviceIp;
}