// #include "ComputerSystem.h"
#include "MemoryHelper.h"
#include <cmath>
#include <iostream>
#include <sys/mman.h>
#include <sys/sem.h>
#include <unistd.h>
#include <cstring>

bool isViolation(aircraftData craft1, aircraftData craft2) {
	float distanceXY = sqrt(((craft1.position.x^2) + (craft2.position.x^2)) + ((craft1.position.y^2) + (craft2.position.y^2)));
	if (distanceXY < 3000.0 && abs(craft1.position.z - craft2.position.z) < 1000) {
		return true;
	} else {
		return false;
	}
}

int main() {
	MemoryHelper memHelp;
	aircraftData datai;
	aircraftData dataj;
	while(1) {
		bool violationFound;
		for (int i = 0; i < 2; i++) {
			for (int j = i+1; j < 3; j++) {
				datai = memHelp.getData(i);
				dataj = memHelp.getData(j);
				violationFound = isViolation(datai, dataj);
			}
		}
		if (violationFound) {
			// printf("\n\n THERE IS A VIOLATION BETWEEN THE AIRPLANES %d & %d", datai.id, dataj.id);
		}
		sleep (5);
	}

	return 0;
}
