#include "MemoryHelper.h"

void MemoryHelper::setData(int id, aircraftData data) {
	std::string temp = "/" + std::to_string(id);
	const char* name = temp.c_str();
	int shm_fd;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	if(shm_fd == -1) {
		//handle error
	}
	ftruncate(shm_fd, sizeof(aircraftData));

	aircraftData* dataPtr = (aircraftData*)mmap(0, sizeof(aircraftData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	*dataPtr = data;

	if(munmap(dataPtr, sizeof(aircraftData)) == -1) {
		//handle error
	}
}

aircraftData MemoryHelper::getData(int id) {
	aircraftData data;
	std::string temp = "/" + std::to_string(id);
	const char* name = temp.c_str();
	int shm_fd;
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if(shm_fd == -1) {
		//handle error
	}

	aircraftData* dataPtr = (aircraftData*)mmap(0, sizeof(aircraftData), PROT_READ, MAP_SHARED, shm_fd, 0);
	data = *dataPtr;
	if(munmap(dataPtr, sizeof(aircraftData)) == -1) {
		//handle error
	}
	return(data);
}

void MemoryHelper::closeMemory(int id) {
	std::string temp = "/" + std::to_string(id);
	const char* name = temp.c_str();
	int shm_fd;
	shm_fd = shm_open(name, O_RDONLY, 0666);
	close(shm_fd);
}
