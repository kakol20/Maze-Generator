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

	// generate grid
	int cols = 10, rows = 10;

	std::cout << "Set Width: \n";
	std::cin >> cols;

	std::cout << "Set Height: \n";
	std::cin >> rows;

	for (int x = 0; x < cols; x++) {
		std::vector<Cell*> yGrid;

		for (int y = 0; y < rows; y++) {
			yGrid.push_back(new Cell(x, y));
		}

		grid.push_back(yGrid);
	}

	// generate maze
	std::vector<Cell*> stack;
	grid[0][0]->SetVisited(true);

	int currentX = 0;
	int currentY = 0;

	stack.push_back(grid[0][0]);

	while (!stack.empty()) {
		// Pop a cell from the stack and make it a current cell
		currentX = stack.back()->GetX();
		currentY = stack.back()->GetY();
		stack.pop_back();

		// If the current cell has any neighbours which have not been visited
		std::vector<Side> neighbours;

		// up
		if (currentY != 0) {
			if (!grid[currentX][currentY - 1]->GetVisited()) neighbours.push_back(Side::UP);
		}

		// down
		if (currentY < rows - 1) {
			if (!grid[currentX][currentY + 1]->GetVisited()) neighbours.push_back(Side::DOWN);
		}

		// left
		if (currentX != 0) {
			if (!grid[currentX - 1][currentY]->GetVisited()) neighbours.push_back(Side::LEFT);
		}

		// right
		if (currentX < cols - 1) {
			if (!grid[currentX + 1][currentY]->GetVisited()) neighbours.push_back(Side::RIGHT);
		}

		if (!neighbours.empty()) {
			// Push the current cell to the stack
			stack.push_back(grid[currentX][currentY]);

			// Choose one of the unvisited neighbours
			float random = LinearFeedbackShift::RandFRange(0.0f, (float)(neighbours.size()));
			int index = (int)floorf(random);
			Side chosen = neighbours[index];

			// Remove the wall between the current cell and the chosen cell
			// Mark the chosen cell as visited and push it to the stack
			grid[currentX][currentY]->SetSide(true, chosen);
			switch (chosen) {
			case Side::DOWN:
				grid[currentX][currentY + 1]->SetSide(true, Side::UP);
				grid[currentX][currentY + 1]->SetVisited(true);

				stack.push_back(grid[currentX][currentY + 1]);
				break;

			case Side::LEFT:
				grid[currentX - 1][currentY]->SetSide(true, Side::RIGHT);
				grid[currentX - 1][currentY]->SetVisited(true);

				stack.push_back(grid[currentX - 1][currentY]);
				break;

			case Side::RIGHT:
				grid[currentX + 1][currentY]->SetSide(true, Side::LEFT);
				grid[currentX + 1][currentY]->SetVisited(true);

				stack.push_back(grid[currentX + 1][currentY]);
				break;

			case Side::UP:
				grid[currentX][currentY - 1]->SetSide(true, Side::DOWN);
				grid[currentX][currentY - 1]->SetVisited(true);

				stack.push_back(grid[currentX][currentY - 1]);
				break;
			}
		}
	}

	// set entry and exit
	grid[0][0]->SetSide(true, Side::UP);
	grid[cols - 1][rows - 1]->SetSide(true, Side::DOWN);

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