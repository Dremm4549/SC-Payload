#define CROW_MAIN

#include "crow_all.h"
#include <iostream>

int main()
{
	crow::SimpleApp app;

	//All routes in this main are subject to modification. This just provides a baseline to use so that 1. We have an idea of what routes we need to handle and 2. Other services will be able to communicate with our service.
	//Current routes are not necessarily final either. The syntax for the routes may need to be changed, some routes can be added/removed, logic obviously still needs to be added for the routes as well.
	//It should also be known that as of now, these routes have not been tested to even see if they work properly. 
	CROW_ROUTE(app, "/ChangeState")
		([](const request& req, response& res) {
			
		});

	CROW_ROUTE(app, "/Telemetry")
		([](const request& req, response& res) {

		});
	return 0;
}
