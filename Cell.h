#ifndef CELL_H
#define CELL_H

class Cell {
public:
	Cell();
	Cell(const int col, const int row);
	
	static enum class Side {
		UP, RIGHT, DOWN, LEFT
	};

	~Cell();

private:
	int m_col;
	int m_row;
};

#endif // !CELL_H
