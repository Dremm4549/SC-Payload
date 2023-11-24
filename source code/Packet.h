#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <cstring>
#include "json.hpp"
#include <map>

/**
 * @brief Class for handling packet data based on a defined protocol.
 *
 * This class is responsible for managing data packets, including packetization
 * of data, sending, and receiving. It utilizes JSON for structuring packet data.
 */
class Packet
{
private:
	std::vector<unsigned char> packetData; ///< The raw data to be packetized.
	static const int packetSize = 66560; ///< Fixed size of each packet.
	static const int seqNumFlagSize = sizeof(int); ///< Size of sequence number flag.
	static const int endFlagSize = sizeof(int); ///< Size of end flag.

	string IP[7]; ///< Array of IP addresses.
	std::string destinationID; ///< Destination identifier for the packet.
	std::string sourceID; ///< Source identifier for the packet.
	std::map<int, std::string> serviceDictionary;

public:
	std::vector<nlohmann::json> Packets; ///< Vector of JSON objects representing packets.
	/**
	 * @brief Default constructor for the Packet class.
	 */
	Packet();
	/**
	 * @brief Construct a new Packet object with initial data.
	 *
	 * @param inputData The data to be used for packetization.
	 * @param destID The destination ID for the packet.
	 * @param srcID The source ID for the packet.
	 */
	Packet(const std::vector<unsigned char>& inputData, const std::string& destID, const std::string& srcID);
	/**
	 * @brief Packetizes the data into JSON objects.
	 *
	 * This function divides the data into packets, each represented by a JSON object.
	 * The function calculates the number of packets required and fills each packet with
	 * the appropriate data segment.
	 */
	void Packetize();
	/**
	 * @brief Sends data packets (stub function for demonstration).
	 */
	void Send();
	/**
	 * @brief Receives data packets (stub function for demonstration).
	 */
	void Recieve();
	/**
	 * @brief Gets the IP address for a given service number.
	 *
	 * @param servicenum The service number for which to retrieve the IP address.
	 * @return string The IP address corresponding to the service number.
	 */
	string getIP(int servicenum);
	/**
	 * @brief Reads and initializes the IP addresses (to be implemented).
	 */
	void readIP();
	/**
	 * @brief Debugger method to just see what services ips exist in dictionary.
	 */
	void PrintIp();
	/**
	 * @brief Cheks if service exsits
	 */
	bool FindService(int serviceID);
	/**
	 * @brief returns service ip
	 */
	std::string GetServiceIP(int serviceID);
};
