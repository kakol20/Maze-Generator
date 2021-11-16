#include "Cell.h"

Cell::Cell() {
	m_col = 0;
	m_row = 0;
}

Cell::Cell(const int col, const int row) {
	m_col = col;
	m_row = row;
}

Cell::~Cell() {
}
