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

void Cell::SetSide(const bool flag, const Side side) {
	switch (side) {
	case Side::UP:
		m_up = flag;
		break;

	case Side::RIGHT:
		m_right = flag;
		break;

	case Side::DOWN:
		m_down = flag;
		break;

	case Side::LEFT:
		m_left = flag;
		break;
	}
}

void Cell::SetVisited(const bool flag) {
	m_visited = flag;
}

bool Cell::GetVisited() {
	return m_visited;
}

int Cell::GetX() {
	return m_col;
}

int Cell::GetY() {
	return m_row;
}

Cell::~Cell() {
}