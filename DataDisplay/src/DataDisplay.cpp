#include "MemoryHelper.h"

#include <iostream>
#include <vector>
#include <unistd.h>
#include <iomanip>


class DataDisplay {
public:
    int width, height;
    std::vector<std::vector<char>> grid;

    DataDisplay(int w, int h) : width(w), height(h) {
        grid.resize(height, std::vector<char>(width, '.'));
    }

    void placeDot(int id, int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
        		grid[y][x] = id + '0';
        }
    }


    void print() {
            std::cout << "  ";
            for (int i = 0; i < width; ++i) {
                std::cout << "\t " << i;
            }
            std::cout << std::endl;

            for (int i = 0; i < height; ++i) {
                std::cout << i << "\t ";

                for (int j = 0; j < width; ++j) {
                    std::cout << grid[i][j] << "\t ";
                }

                std::cout << std::endl;
            }
        }
};

int main() {
	DataDisplay grid(10, 10);
    MemoryHelper memHelp;

    // this section here should pull information from the computersystem for aircraft information

    aircraftData data;
	while (1) {

		for(int i = 0; i < 2; i++) {
			data = memHelp.getData(i);
			grid.placeDot(data.id, data.position.x/10000, data.position.y/10000);
		}
		grid.print();
	    sleep(5);
	}



    return 0;
}
