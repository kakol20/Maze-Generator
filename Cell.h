#ifndef CELL_H
#define CELL_H

enum class Side {
	UP, RIGHT, DOWN, LEFT
};

class Cell {
public:
	Cell();
	Cell(const int col, const int row);

	bool GetSide(Side side);
	void SetSide(const bool flag, const Side side);

	bool GetVisited();
	void SetVisited(const bool flag);

	int GetX();
	int GetY();

	~Cell();

private:
	int m_col;
	int m_row;

	bool m_up = false;
	bool m_right = false;
	bool m_down = false;
	bool m_left = false;

	bool m_visited = false;
};

#endif // !CELL_H
