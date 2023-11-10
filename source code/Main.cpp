#define CROW_MAIN

#include "crow_all.h"
#include "Payload.h"
#include "imageData.h"
#include "Packet.h"
#include <iostream>

int main()
{

	crow::SimpleApp app;
	Payload payloadObj; //create payload object
	ImageData imageDataObj; //create image data object

	//All routes in this main are subject to modification. This just provides a baseline to use so that 1. We have an idea of what routes we need to handle and 2. Other services will be able to communicate with our service.
	//Current routes are not necessarily final either. The syntax for the routes may need to be changed, some routes can be added/removed, logic obviously still needs to be added for the routes as well.
	//It should also be known that as of now, these routes have not been tested to even see if they work properly. 

    // Correct the lambda function declaration

	CROW_ROUTE(app, "/")([](){
    return "Hello world";
	});

	CROW_ROUTE(app, "/Image")([](){
    return "Hello world";
	});

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
				jsonResp["data"]["Sequence number"] = 1;
				jsonResp["data"]["message"] = "Payload is on";
			}
			else if(strcmp(state, "false") == 0){
				payloadObj.SetPowerState(false);
				res.code = 200;
				jsonResp["Verb"] = "PUT";
				jsonResp["Source"] = "ourId";
				jsonResp["destination"] = "theirId";
				jsonResp["numPacketsExpected"] = 1;
				jsonResp["data"]["Sequence number"] = 1;
				jsonResp["data"]["message"] = "Payload is off";
			}
		}

		res.set_header("Content-Type", "application/json");
        res.write(jsonResp.dump());
        res.end();
    });

	CROW_ROUTE(app, "/Telemetry")
		([](const crow::request& req, crow::response& res) {

		});

	CROW_ROUTE(app, "/DownloadImage")
			.methods("GET"_method)
	([&imageDataObj](const crow::request& req, crow::response& res) {
		const char* state = req.url_params.get("state");
		crow::json::wvalue jsonResp;

		imageDataObj.downloadImage();
		jsonResp["message"] = "IMAGE READ";
		res.code = 200;

		res.set_header("Content-Type", "application/json");
		res.write(jsonResp.dump());
		res.end();
	});	

	CROW_ROUTE(app, "/CaptureImage")
	([](const crow::request& req, crow::response& res) {

	});

	app.port(27000).multithreaded().run();
    return 0;
}
