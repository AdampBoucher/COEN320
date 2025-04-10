#ifndef COMPUTERSYSTEM_H_
#define COMPUTERSYSTEM_H_

#include <vector>
#include <string>
#include "MemoryHelper.h"

class ComputerSystem {
public:
    ComputerSystem();
    ~ComputerSystem();

    // Initializes the computer system and shared memory
    bool initialize();

    // Start all systems (radar, aircraft, etc.)
    void startSystems();

    // Stop the computer system (shut down or clean up resources)
    void stopSystems();

    // Handle incoming messages from the communication system
    void processIncomingMessages();

    // Displays system status (can be used for logging or debugging)
    void displaySystemStatus() const;

    bool isViolation(aircraftData datai, aircraftData dataj);

private:

    // Shared memory structure to access aircraft and system data
    SharedAirspace* shm;

    // Internal methods for system management
    void manageAircraft();
    void manageRadarSystem();

    // Function to create and initialize shared memory
    bool createSharedMemory(bool isCreator);
};

#endif /* COMPUTERSYSTEM_H_ */
