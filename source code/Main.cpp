#define CROW_MAIN

#include "crow_all.h"
#include "Payload.h"
#include "Telem.h"
#include "ImageData.h"
#include "Packet.h"
#include <iostream>

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

	CROW_ROUTE(app, "/")([]() {
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
		if (state) {
			if (strcmp(state, "true") == 0 && payloadObj.GetPowerState() == false) {
				payloadObj.SetPowerState(true);
				res.code = 200;
			}
			else if(strcmp(state, "false") == 0 && payloadObj.GetPowerState() == true){
				payloadObj.SetPowerState(false);
				res.code = 200;
			}
			else
			{
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

		if(readVal){
			if(readVal.has("long") && readVal.has("lat") && readVal.has("Time")&& payloadObj.GetPowerState() == true){
				res.code = 200;
				double longV = readVal["long"].d();
				double lat = readVal["lat"].d();
				std::string time = readVal["Time"].d();


				telemetryObj.setTelem((float)longV,(float)lat,(std::string)time);
			}
			else
			{
				res.code = 400;

			}
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

	CROW_ROUTE(app, "/downloadImage")
	.methods("GET"_method)
	([&imageDataObj, &telemetryObj](const crow::request& req, crow::response& res) {
		crow::json::wvalue jsonResp;

		jsonResp["Status"] = "IMAGE READ";
		jsonResp["Data"]["image"] = imageDataObj.getImage();
		jsonResp["data"]["Long"] = telemetryObj.getLong();
		jsonResp["data"]["lat"] = telemetryObj.getLat();
		jsonResp["data"]["time"] = telemetryObj.getTime();
		res.code = 200;

		res.set_header("Content-Type", "application/json");
		res.write(jsonResp.dump());
		res.end();
	});	


	app.port(8080).multithreaded().run();
    return 0;
}
