#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // for sleep()
#include <time.h>
#include <iostream>
#include <string>

#include "SharedData.h"
#include "SharedMemory.h"

int main() {
    SharedAirspace* shm = createSharedMemory(false);

    while (true) {
        sleep(5);

        sem_wait(&shm->mutex);
        int n = shm->n_seconds;
        for (int i = 0; i < MAX_AIRCRAFT; ++i) {
            if (!shm->aircraftList[i].active) continue;

            for (int j = i + 1; j < MAX_AIRCRAFT; ++j) {
                if (!shm->aircraftList[j].active) continue;

                bool current = isViolation(shm->aircraftList[i], shm->aircraftList[j], 0);
                bool future = isViolation(shm->aircraftList[i], shm->aircraftList[j], n);

                if (current) {
                    std::cout << "[ALERT] Immediate violation between "
                              << shm->aircraftList[i].id << " and " << shm->aircraftList[j].id << "\n";
                } else if (future) {
                    std::cout << "[WARNING] Violation expected in " << n
                              << "s between " << shm->aircraftList[i].id
                              << " and " << shm->aircraftList[j].id << "\n";
                }
            }
        }
        sem_post(&shm->mutex);
    }

    return 0;
}
