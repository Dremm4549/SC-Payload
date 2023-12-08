#define CROW_MAIN

#include "crow_all.h"
#include "Payload.h"
#include "Telem.h"
#include "ImageData.h"
#include "Packet.h"
#include <iostream>
#include "HTTPRequest.hpp"

#define MAXBUFFERSIZE 65536
using json = nlohmann::json;

std::string GetTimeStamp()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t tt = std::chrono::system_clock::to_time_t(now);
	std::tm localTime = *std::localtime(&tt);
///yyyy__
	std::stringstream ss;
	ss << std::put_time(&localTime, "%Y%m%d_%H%M%s");
	return ss.str();
}

int main()
{

	crow::SimpleApp app;
	Payload payloadObj; //create payload object
	ImageData imageDataObj; //create image data object
	Telem telemetryObj;
	Packet packetObj;

	packetObj.readIP();
	packetObj.PrintIp();
	//All routes in this main are subject to modification. This just provides a baseline to use so that 1. We have an idea of what routes we need to handle and 2. Other services will be able to communicate with our service.
	//Current routes are not necessarily final either. The syntax for the routes may need to be changed, some routes can be added/removed, logic obviously still needs to be added for the routes as well.
	//It should also be known that as of now, these routes have not been tested to even see if they work properly. 



	/// <summary>
	/// This route listens for a put request that and querys 
	//  a true or false paramter from the url use to alter the state
	/// </summary>

	CROW_ROUTE(app, "/payloadState")
		.methods("PUT"_method)
		([&payloadObj](const crow::request& req, crow::response& res) {
		const char* state = req.url_params.get("state");
		crow::json::wvalue jsonResp;
		if (state) {
			if (strcmp(state, "true") == 0) {
				payloadObj.SetPowerState(true);
				jsonResp["Status"] = "True";
				res.code = 200;
			}
			else if(strcmp(state, "false") == 0){
				payloadObj.SetPowerState(false);
				jsonResp["Status"] = "False";
				res.code = 200;
			}
			else
			{
				jsonResp["Status"] = "Error";
				res.code = 400;
			}
		}

		res.set_header("Content-Type", "application/json");
		res.write(jsonResp.dump());
		res.end();
			});

	/// <summary>
	/// This route will return the current power state 
	/// of the payload 
	/// </summary>
	CROW_ROUTE(app, "/GetPayloadState")
		.methods("GET"_method)
		([&payloadObj](const crow::request& req, crow::response& res) {
		crow::json::wvalue jsonResp;
		if (payloadObj.GetPowerState() == false)
		{
			res.code = 503;
		}
		else
		{
			jsonResp["data"]["message"] = payloadObj.GetPowerState();
			res.code = 200;
		}

		res.set_header("Content-Type", "application/json");
		res.write(jsonResp.dump());
		res.end();
			});

	/// <summary>
	/// This route will be responsible for setting the telemetry 
	///within image meta data
	/// </summary>


	/// <summary>
	/// SetTelemetry route will change the current telememtry values in the 
	/// Gets the latest telemtery values from the telemetry object
	/// </summary>
	CROW_ROUTE(app, "/Telemetry")
		.methods("GET"_method)
		([&telemetryObj, &payloadObj](const crow::request& req, crow::response& res) {
			crow::json::wvalue jsonResp;
			if (payloadObj.GetPowerState() == false)
			{
				res.code = 503;
			}
			else
			{
				res.code = 200;
				jsonResp["data"]["Long"] = telemetryObj.getLong();
				jsonResp["data"]["lat"] = telemetryObj.getLat();
				jsonResp["data"]["temp"] = telemetryObj.getTime();
			}

			res.set_header("Content-Type", "application/json");
			res.write(jsonResp.dump());
			res.end();
		});

	/// <summary>
	/// SetTelemetry route will change the current telememtry values in the 
	/// Telemtry object
	/// </summary>
	CROW_ROUTE(app, "/SetTelemetry")
	.methods("PUT"_method)
	([&telemetryObj, &payloadObj](const crow::request& req, crow::response& res) {
		crow::json::wvalue jsonResp;
		crow::json::rvalue readVal;

		readVal = crow::json::load(req.body);
			if(!payloadObj.GetPowerState()){
				if(readVal){
				if(readVal.has("long") && readVal.has("lat") && readVal.has("Time")&& payloadObj.GetPowerState() == true){
					res.code = 200;
					double longV = readVal["long"].d();
					double lat = readVal["lat"].d();
					std::string time = readVal["Time"].s();

					telemetryObj.setTelem((float)longV,(float)lat,(std::string)time);
				}
				else
				{
					res.code = 400;

				}
			}
		} else {
			res.code = 503;
		}
		

		res.set_header("Content-Type", "application/json");
		res.write(jsonResp.dump());
		res.end();
	});

	/// <summary>
	/// Download image is get request that will retreive a random photo
	/// from the paylaods filesystem and perform some background operations converting
	/// the binary into hexademical and pactektizing it for transmission
	/// </summary>

	CROW_ROUTE(app, "/DownloadImage")
	.methods("GET"_method)
	([&imageDataObj, &payloadObj, &packetObj](const crow::request& req, crow::response& res) {
		crow::json::wvalue jsonResp;

		if(payloadObj.GetPowerState())
		{
			std::string selectedImage = imageDataObj.GenerateNewImage();
			std::cout << selectedImage << std::endl;
			imageDataObj.OpenImage(selectedImage);
		//	imageDataObj.SetImageFileSize();
			//imageDataObj.AllocateImageBuffer(imageDataObj.GetImageFileSize());
			//jsonResp["size"] = imageDataObj.GetImageFileSize();
			imageDataObj.StoreImageInMemmory();
			imageDataObj.CloseImage();

			if(packetObj.FindService(5))
			{
				std::string serviceIp = packetObj.GetServiceIP(1);
				std::string sourceAddress = packetObj.GetServiceIP(2);
				std::cout << "can send request to " << serviceIp << std::endl;
			}
			else{
				std::cout << "ERROR: cant find dest IP" << std::endl;
				return;
			}
		
			int i = 0;
			int byteCounter = 0;
			int packetNum = 0;

			std::string imgHex = imageDataObj.GetImageHex();
			imageDataObj.CloseImage();

			//calculate the number of packets that need to send
			float packetToBeSent = (float)imgHex.size() / (float)MAXBUFFERSIZE;
			int packetRemainder = imageDataObj.GetImageFileSize() % MAXBUFFERSIZE;
			std::cout << "The buffer has: " << imageDataObj.GetImageFileSize() << std::endl << " This many characters in string " << imgHex.size() << std::endl;
			std::cout << "The packets to be sent has: " << packetToBeSent << " and this many remaning bytes remaning" << packetRemainder<< std:: endl;

			// if(packetRemainder > 0){
			// 	packetToBeSent += 1;
			// }		

			std:string respStr = "";
			std::string sendStr = "";
			std::string payloadOpIp = packetObj.GetServiceIP(7) + "/payloadimage";
			std:: cout << payloadOpIp;
			while(imgHex[i] != '\0')
			{
				sendStr += imgHex[i];
				
				if (byteCounter == MAXBUFFERSIZE) 
				{
					//send 
					try
					{
						json j;
						j["raw"] = sendStr;
						j["verb"] = "POST";
						j["source"] = "2";
						j["URI"] = payloadOpIp;
						j["sequencenumber"] = packetNum;
						std::string timeStamp = "6";
						j["ID"] = timeStamp;
						
						if(packetNum == packetToBeSent)
						{
							j["finflag"] = true;
							std::cout << "sending fin" << std::endl;
						}
						else
						{
							j["finflag"] = false;
						}

						std::string body = j.dump();
						
						http::Request request{"http://" + packetObj.GetServiceIP(2) + ":8080/downloadImage"};
					
						const auto response = request.send("POST", body, {
						{"Content-Type", "application/json"}
						});
					
						byteCounter = 0;
						sendStr.clear();
						std::cout << std::string{response.body.begin(), response.body.end()} << '\n';
						
					}
					catch(const std::exception& e)
					{
						std::cerr << "Request failed, error: " << e.what() << '\n';
					}
					
					sendStr.clear();
					std::cout << packetNum << "out of " << packetToBeSent << std::endl;
					packetNum++;
				}

				i++;
				byteCounter++;
			}

			// if(byteCounter > 0 && packetRemainder > 0)
			// {
			// 	std::cout << " current str size " << imgHex.size() << std::endl;
			// 	std::cout << "Okay start from" << i << " Go till " << imgHex.size() << " current str: "<< sendStr << std::endl;
				
			// }

			if (byteCounter > 0 && packetRemainder > 0) 
			{
				//send
				try
				{
					http::Request request{"http://" + packetObj.GetServiceIP(2) + ":8080/downloadImage"};
					json j;
					j["raw"] = sendStr;
					j["sequencenumber"] = packetNum;
					std::string timeStamp = "6";
					j["ID"] = timeStamp;
					j["finflag"] = true;
					std::cout << " if caluse sending fin" << std::endl;
					std::string body = j.dump();

					const auto response = request.send("POST", body, {
					{"Content-Type", "application/json"}
					});
				
					std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
				}
				catch(const std::exception& e)
				{
					std::cerr << "Request failed, error: " << e.what() << '\n';
				}

				sendStr.clear();
				packetNum++;
				std::cout << packetNum << "out of " << packetToBeSent << std::endl;
				byteCounter = 0;
			}
			
			res.code = 200;
			jsonResp["Status"] = "SUCCESS";
		}
		else
		{
			res.code = 400;
		}
	
		
		res.set_header("Content-Type", "application/json");
		res.write(jsonResp.dump());
		res.end();
	});	


	app.port(8080).multithreaded().run();
    return 0;
}
