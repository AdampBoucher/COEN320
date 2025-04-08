#include "ComputerSystem.h"
#include <iostream>
#include <sys/mman.h>
#include <sys/sem.h>
#include <unistd.h>
#include <cstring>

// Constructor
ComputerSystem::ComputerSystem() {
    shm = nullptr;  // Initialize shared memory pointer
}

// Destructor
ComputerSystem::~ComputerSystem() {
    stopSystems();
    // Cleanup shared memory if needed
}

// Create or access shared memory
bool ComputerSystem::createSharedMemory(bool isCreator) {
    // Generate unique key for shared memory
    key_t key = ftok("/tmp", 'R');

    if (key == -1) {
        std::cerr << "Error: Could not generate key for shared memory." << std::endl;
        return false;
    }

    // Initialize shared memory (only if we are the creator)
    if (isCreator) {
        memset(shm, 0, sizeof(SharedAirspace));  // Clear the shared memory
        std::cout << "Shared memory initialized." << std::endl;
    }

    return true;
}

// Initialize the computer system, set up components like comms, display, etc.
bool ComputerSystem::initialize() {
    if (!createSharedMemory(true)) {
        std::cerr << "Error: Failed to create shared memory." << std::endl;
        return false;
    }

    std::cout << "Computer System Initialized!" << std::endl;
    return true;
}

// Start the individual components of the computer system (e.g., radar, aircraft)
void ComputerSystem::startSystems() {
    // Start aircraft systems using shared memory (simulated here)
    manageAircraft();
    manageRadarSystem();

    std::cout << "Systems Started!" << std::endl;
}

// Stop or clean up all systems
void ComputerSystem::stopSystems() {
    // Example of cleaning up shared memory (detach and remove)
    // shmdt(shm);
    std::cout << "Systems Stopped!" << std::endl;
}

// Process incoming messages (from the CommSystem)
void ComputerSystem::processIncomingMessages() {
//    CommMessage message;
//    while (commSystem.receiveMessage(message)) {
//        std::cout << "Processing incoming message: " << message.command << std::endl;
//        commSystem.processMessage(message);
//    }
}

// Display the status of the system (useful for debugging or logging)
void ComputerSystem::displaySystemStatus() const {
    std::cout << "Displaying System Status..." << std::endl;
    // dataDisplay.displayAllAircraft();  // Display data from shared memory
}

// Manage aircraft (update, simulate, etc.)
void ComputerSystem::manageAircraft() {
    // Example: Update shared memory with aircraft data
    SharedAirspace& airspace = *shm;
//    AircraftData data1 = {1, 1000, 1000, 10000, 200, 150, 300, true};
//    AircraftData data2 = {2, 1200, 1500, 15000, 220, 180, 310, true};

    // Add aircraft data to shared memory (simplified example)
//    airspace.aircraftList.push_back(data1);
//    airspace.aircraftList.push_back(data2);

    // Update display system (can read from shared memory)
//    dataDisplay.addAircraftData(data1);
//    dataDisplay.addAircraftData(data2);
}

// Manage the radar system (this can be expanded to include radar-specific logic)
void ComputerSystem::manageRadarSystem() {
    std::cout << "Managing Radar System..." << std::endl;
}

