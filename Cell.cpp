#include "Cell.h"

Cell::Cell() {
	m_col = 0;
	m_row = 0;
}

Cell::Cell(const int col, const int row) {
	m_col = col;
	m_row = row;
}

bool Cell::GetSide(Side side) {
	switch (side) {
	case Side::UP:
		return m_up;

	case Side::RIGHT:
		return m_right;

	case Side::DOWN:
		return m_down;

	case Side::LEFT:
		return m_left;

	default:
		return false;
	}

	return false;
}

Cell::~Cell() {
}
