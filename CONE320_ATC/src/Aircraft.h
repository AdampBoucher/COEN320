#ifndef SRC_AIRCRAFT_H_
#define SRC_AIRCRAFT_H_

#define AIRCRAFT_CALLBACK_RATE 1

#include <time.h>
#include <pthread.h>
#include <sys/siginfo.h>
#include <unistd.h>
#include <stdio.h>
#include "MemoryHelper.h"

class Aircraft {
public:
	Aircraft();
	Aircraft(int id, int arrivalTime, position_t arrivalPosition, speed_t arrivalSpeed);
	void init(int id, int arrivalTime, position_t arrivalPosition, speed_t arrivalSpeed);

	void start();
	void join();

	// === Optional: For console debugging ===
	void printStatus() const {
		printf("Aircraft %d → Pos(%d, %d, %d) Vel(%d, %d, %d)\n",
			id,
			position.x, position.y, position.z,
			speed.x, speed.y, speed.z);
	}

private:
	bool planeArrived;
	bool planeLeft;
	int id;
	int arrivalTime;
	position_t position;
	speed_t speed;
	MemoryHelper memoryHelper;

	pthread_t thread;

	static void* startThread(void*);
	static void timerCallback(union sigval);
	void update(void);
	aircraftData updateAircraftData();
};

#endif /* SRC_AIRCRAFT_H_ */
