#define CROW_MAIN

#include "crow_all.h"
#include "Payload.h"
#include "Telem.h"
#include "ImageData.h"
#include "Packet.h"
#include <iostream>
#include "HTTPRequest.hpp"

#define MAXBUFFERSIZE 65536


std::string GetTimeStamp()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	std::time_t tt = std::chrono::system_clock::to_time_t(now);

	std::tm localTime = *std::localtime(&tt);

	std::stringstream ss;
	ss << std::put_time(&localTime, "%Y%m%d_%H%M%S");
	return ss.str();

}
int main()
{

	crow::SimpleApp app;
	Payload payloadObj; //create payload object
	ImageData imageDataObj; //create image data object
	Telem telemetryObj;

	//All routes in this main are subject to modification. This just provides a baseline to use so that 1. We have an idea of what routes we need to handle and 2. Other services will be able to communicate with our service.
	//Current routes are not necessarily final either. The syntax for the routes may need to be changed, some routes can be added/removed, logic obviously still needs to be added for the routes as well.
	//It should also be known that as of now, these routes have not been tested to even see if they work properly. 

    // Correct the lambda function declaration

	CROW_ROUTE(app, "/")([](){
    return "Hello world";
	});

	/// <summary>
	/// This route listens for a put request that and querys 
	//  a true or false paramter from the url use to alter the state
	/// </summary>

    CROW_ROUTE(app, "/payloadState")
	.methods("PUT"_method)
    ([&payloadObj](const crow::request& req, crow::response& res) {
		const char* state = req.url_params.get("state");
		crow::json::wvalue jsonResp;
		if(state){
			if(strcmp(state, "true") == 0){
				payloadObj.SetPowerState(true);
				jsonResp["Verb"] = "PUT";
				jsonResp["Source"] = "ourId";
				jsonResp["destination"] = "theirId";
				jsonResp["numPacketsExpected"] = 1;
				jsonResp["data"]["message"] = "Payload is on";
			}
			else if(strcmp(state, "false") == 0){
				payloadObj.SetPowerState(false);
				res.code = 200;
				jsonResp["Verb"] = "PUT";
				jsonResp["Source"] = "ourId";
				jsonResp["destination"] = "theirId";
				jsonResp["numPacketsExpected"] = 1;
				jsonResp["data"]["message"] = "Payload is off";
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
		jsonResp["Verb"] = "GET";
		jsonResp["Source"] = "ourID";
		jsonResp["destination"] = "theirID";
		jsonResp["data"]["message"] = payloadObj.GetPowerState();
				
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
		([&telemetryObj](const crow::request& req, crow::response& res) {
			crow::json::wvalue jsonResp;
			
			res.code = 200;
			jsonResp["Status"] = "OK";
			jsonResp["data"]["Long"] = telemetryObj.getLong();
			jsonResp["data"]["lat"] = telemetryObj.getLat();
			jsonResp["data"]["temp"] = telemetryObj.getTime();

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
	([&telemetryObj](const crow::request& req, crow::response& res) {
		crow::json::wvalue jsonResp;
		crow::json::rvalue readVal;

		readVal = crow::json::load(req.body);

		if(readVal){
			if(readVal.has("long") && readVal.has("lat") && readVal.has("Time")){
				res.code = 200;
				double longV = readVal["long"].d();
				double lat = readVal["lat"].d();
				double temp = readVal["Time"].d();

				telemetryObj.setTelem((float)longV,(float)lat,(float)temp);
				
				jsonResp["Data"]["Long"] = telemetryObj.getLong();
				jsonResp["Data"]["lat"] = telemetryObj.getLat();
				jsonResp["Data"]["time"] = telemetryObj.getTime();
			}
		}
		
		res.code = 200;
		jsonResp["status"] = "SUCCESS";	

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
	([&imageDataObj,&payloadObj](const crow::request& req, crow::response& res) {
		crow::json::wvalue jsonResp;

		if(payloadObj.GetPowerState())
		{
			imageDataObj.OpenImage("../../SpaceImages/Image4.jpg");
			imageDataObj.SetImageFileSize();
			imageDataObj.AllocateImageBuffer(imageDataObj.GetImageFileSize());
			jsonResp["Status"] = imageDataObj.GetImageFileSize();
			imageDataObj.StoreImageInMemmory();
		
			int i = 0;
			int byteCounter = 0;
			int packetNum = 0;

			std::string imgHex = imageDataObj.GetImageHex();
			std:string respStr = "";

			std::string sendStr = "";
			while(imgHex[i] != '\0')
			{
				sendStr += imgHex[i];
				
				if (byteCounter == MAXBUFFERSIZE) 
				{
					//send 
					try
					{
						//cout << "sequenceNum: " << packetNum << endl; GetTimeStamp()
						http::Request request{"http://host.docker.internal:9000/poop"};
						std::string body = "{\"raw\": \"" + sendStr + "\", \"sequenceNumber\": " + std::to_string(packetNum) + ", \"ID\": \"" + GetTimeStamp() + "\"}";
						const auto response = request.send("POST", body, {
						{"Content-Type", "application/json"}
						});
					
						
						//std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
					}
					catch(const std::exception& e)
					{
						std::cerr << "Request failed, error: " << e.what() << '\n';
					}

					sendStr.clear();
					byteCounter = 0;
					packetNum++;
				}

				i++;
				byteCounter++;
			}

			if (byteCounter > 0) 
			{
				//send
				try
				{
					http::Request request{"http://host.docker.internal:9000/poop"};
					std::string body = "{\"data\": \"" + sendStr + "\", \"sequenceNumber\": " + std::to_string(packetNum) + "}";
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
				byteCounter = 0;
			}
			imageDataObj.CloseImage();
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

	/// <summary>
	/// Similar to the Download image but its supposed to 
	/// represnt the act of taking a photo from space.
	/// </summary>

	CROW_ROUTE(app, "/CaptureImage")
	.methods("GET"_method)
	([](const crow::request& req, crow::response& res) {
		crow::json::wvalue jsonResp;
		res.code = 200;
		jsonResp["Status"] = "OK";

		res.set_header("Content-Type", "application/json");
		res.write(jsonResp.dump());
		res.end();
	});

	app.port(8080).multithreaded().run();
    return 0;
}
