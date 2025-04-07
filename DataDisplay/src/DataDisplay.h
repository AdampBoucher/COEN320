#ifndef DATADISPLAY_H_
#define DATADISPLAY_H_

#include <vector>
#include <string>

// Structure to hold aircraft data
struct AircraftData {
    int id;            // Unique identifier for each aircraft
    int posX, posY, posZ;  // Position coordinates (X, Y, Z)
    int spdX, spdY, spdZ;  // Speed components (X, Y, Z)
    bool active;       // Is the aircraft currently active?
};

// Class to manage data display functionality
class DataDisplay {
public:
    // Constructor
    DataDisplay();
    // Destructor
    ~DataDisplay();

    // Initializes the DataDisplay system (could be extended for UI, external interfaces, etc.)
    bool initialize();

    // Adds an aircraft's data to the display system
    void addAircraftData(const AircraftData& aircraftData);

    // Displays the data of all active aircraft
    void displayAllAircraft() const;

    // Updates the display (in case of data changes like position updates)
    void updateDisplay();

    // Optional: For debugging purposes, display a summary of the system's current state
    void displaySystemStatus() const;

private:
    std::vector<AircraftData> aircraftList;  // List of all aircraft being displayed
};

#endif /* DATADISPLAY_H_ */
