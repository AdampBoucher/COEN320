/*
 * MemoryHelper.h
 *
 *  Created on: Apr 7, 2025
 *      Author: ad_bouc
 */

#ifndef MEMORYHELPER_H_
#define MEMORYHELPER_H_

#include <string>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>


typedef struct {
	int x; int y; int z;
} position_t;

typedef struct {
	int x; int y; int z;
} speed_t;

typedef struct {
	speed_t speed;
	position_t position;
	int id;
} aircraftData;

class MemoryHelper {
public:
	MemoryHelper() {};
	void setData(int id, aircraftData data);
	aircraftData getData(int id);
	void closeMemory(int id);

private:

};


#endif /* MEMORYHELPER_H_ */
