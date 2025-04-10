#include "Aircraft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Aircraft::Aircraft() {}

Aircraft::Aircraft(int id, int arrivalTime, position_t arrivalPosition, speed_t arrivalSpeed) :
	id(id),
	arrivalTime(arrivalTime),
	position(arrivalPosition),
	speed(arrivalSpeed),
	thread(0),
	planeArrived(false),
	planeLeft(false) {
}

void Aircraft::init(int id, int arrivalTime, position_t arrivalPosition, speed_t arrivalSpeed) {
	this->id = id;
	this->arrivalTime = arrivalTime;
	this->position = arrivalPosition;
	this->speed = arrivalSpeed;
	this->thread = 0;
	this->planeArrived = false;
	this->planeLeft = false;
}

void Aircraft::start() {
	this->memoryHelper.setData(id, updateAircraftData());
	int threadId = pthread_create(&thread, NULL, startThread, this);
	if (threadId < 0) {
		printf(":( thread creation failed\n");
	}
}

void Aircraft::update() {
	if (!planeArrived)
		planeArrived = true;

	this->position.x += this->speed.x;
	this->position.y += this->speed.y;
	this->position.z += this->speed.z;
	this->memoryHelper.setData(id, updateAircraftData());

	if (position.x < 0 || position.x > 100000 || position.y < 0 || position.y > 100000 || position.z < 0 || position.z > 25000) {
		planeLeft = true;
	}
}

void* Aircraft::startThread(void* arg) {
	Aircraft* aircraft = reinterpret_cast<Aircraft*>(arg);

	timer_t timer;
	struct sigevent sev;
	struct itimerspec its;

	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = Aircraft::timerCallback;
	sev.sigev_value.sival_ptr = arg;

	if (timer_create(CLOCK_REALTIME, &sev, &timer) == -1) {
		printf("timer create failed\n");
	}

	its.it_value.tv_sec = aircraft->arrivalTime;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = AIRCRAFT_CALLBACK_RATE;
	its.it_interval.tv_nsec = 0;

	if (timer_settime(timer, 0, &its, NULL) == -1) {
		printf("set time failed\n");
	}

	while (!aircraft->planeLeft) {
		sleep(1);
	}

	aircraft->memoryHelper.closeMemory(aircraft->id);

	if(timer_delete(timer) == -1) {
		//handle error
	}

	return NULL;
}

void Aircraft::timerCallback(union sigval arg) {
	Aircraft* aircraft = reinterpret_cast<Aircraft*>(arg.sival_ptr);
	aircraft->update();
}

void Aircraft::join() {
	if (pthread_join(thread, NULL) != 0) {
		printf("join failed\n");
	}
}

aircraftData Aircraft::updateAircraftData(void) {
	aircraftData val;
	val.position = this->position;
	val.speed = this->speed;
	val.id = this->id;
	return(val);
}
