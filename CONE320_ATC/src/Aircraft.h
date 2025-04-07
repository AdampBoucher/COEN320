#ifndef SRC_AIRCRAFT_H_
#define SRC_AIRCRAFT_H_

#define AIRCRAFT_CALLBACK_RATE 1

#include <time.h>
#include <pthread.h>
#include <sys/siginfo.h>
#include <unistd.h>
#include <stdio.h>

typedef struct {
	int x; int y; int z;
} position_t;

typedef struct {
	int x; int y; int z;
} speed_t;

class Aircraft {
public:
	Aircraft();
	Aircraft(int id, int arrivalTime, position_t arrivalPosition, speed_t arrivalSpeed);

	void start();
	void join();

	// Public data members (used during init)
	int id;
	int arrivalTime;
	position_t position;
	speed_t speed;

	// === Getters needed for logger ===
	int getId() const { return id; }

	int getX() const { return position.x; }
	int getY() const { return position.y; }
	int getZ() const { return position.z; }

	int getVx() const { return speed.x; }
	int getVy() const { return speed.y; }
	int getVz() const { return speed.z; }

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

	pthread_t thread;

	static void* startThread(void*);
	static void timerCallback(union sigval);

	void update(void);
};

#endif /* SRC_AIRCRAFT_H_ */
