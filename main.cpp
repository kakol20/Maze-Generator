#include <ctime>
#include <iostream>
#include <vector>

#include "Cell.h"
#include "Image.h"
#include "LinearFeedbackShift.h"

std::vector<std::vector<Cell*>> grid;

unsigned int LinearFeedbackShift::Seed = 0;

int main() {
	// use epoch time as seed
	std::time_t currentTime = time(0);
	LinearFeedbackShift::Seed = static_cast<unsigned int>(currentTime);

	int side = (int)Side::DOWN;

	// generate maze
	int cols = 10, rows = 10;
	for (int x = 0; x < cols; x++) {
		std::vector<Cell*> yGrid;

		for (int y = 0; y < rows; y++) {
			yGrid.push_back(new Cell(x, y));
		}

		grid.push_back(yGrid);
	}

	// save maze as image
	int width = (cols * 2) + 1;
	int height = (rows * 2) + 1;

	Image maze(width, height, 1);

	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			int pixelX = x * 2 + 1;
			int pixelY = y * 2 + 1;

			int index = maze.GetIndex(pixelX, pixelY);
			maze.SetData(index, (uint8_t)255);

			if (grid[x][y]->GetSide(Side::UP)) {
				index = maze.GetIndex(pixelX, pixelY - 1);
				maze.SetData(index, (uint8_t)255);
			}

			if (grid[x][y]->GetSide(Side::DOWN)) {
				index = maze.GetIndex(pixelX, pixelY + 1);
				maze.SetData(index, (uint8_t)255);
			}

			if (grid[x][y]->GetSide(Side::RIGHT)) {
				index = maze.GetIndex(pixelX + 1, pixelY);
				maze.SetData(index, (uint8_t)255);
			}

			if (grid[x][y]->GetSide(Side::LEFT)) {
				index = maze.GetIndex(pixelX - 1, pixelY);
				maze.SetData(index, (uint8_t)255);
			}
		}
	}

	maze.Write("images/maze.png");

	// destroy pointers
	for (int x = 0; x < cols; x++) {
		for (auto p : grid[x]) {
			delete p;
		}
		grid[x].clear();
	}
	grid.clear();

	system("pause");

	return 0;
}