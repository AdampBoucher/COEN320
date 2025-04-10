#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>     
#include <string>

#include "Aircraft.h"
#include "Airspace.h"
#include "Logger.h"
#include "MemoryHelper.h"

int main(void) {
	// puts("Hello World!!!");

	//initialize aircrafts
	int arrivalTime = 2;
	position_t position = {40000, 70000, 100};
	speed_t speed = {1000, 1000, 100};

	Aircraft aircraft[10];

	aircraft[0].init(0, 10, position, speed);
	position.x = 0;
	position.y= 0 ;
	position.z = 0;
	speed.x = 2000;
	speed.y = 2000;
	speed.z = 200;
	aircraft[1].init(1, 20, position, speed);
	aircraft[2].init(2, 20, position, speed);
	for (int i = 0; i < 2; i++)
		aircraft[i].start();

	//initialize

//	while (simulationTime <= 60) {
//		simulationTime++;
//
//		// Log aircraft state every 20 seconds
//		if (simulationTime % 20 == 0) {
//			Logger::logAirspace(airspace, simulationTime);
//		}
//
//		// Prompt for operator input every 5 seconds
//		if (simulationTime % 5 == 0) {
//			std::string input;
//			std::cout << "\n[SIM TIME " << simulationTime << "s] Enter operator command: ";
//			std::getline(std::cin, input);
//
////			OperatorCommand parsedCommand;
////			if (OperatorCommandParser::parse(input, parsedCommand)) {
////				Logger::logCommand(input, simulationTime);
////				std::cout << "Command logged for aircraft: " << parsedCommand.aircraftId << "\n";
////			} else {
////				std::cout << "Invalid command format.\n";
////			}
//		}
//
//		sleep(1);
//	}

	for (int i = 0; i < 2; i++) {
		aircraft[i].join();
	}

	printf("ended\n");
	return EXIT_SUCCESS;
}
