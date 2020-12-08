#include <iostream>
#include <assert.h>
#include "Board.h"

void Board::delete_grid() {
	printf("num col is %d\n", num_cols);
	for (int c = 0; c < num_cols; c++) {
		printf("c is %d\n",c);
		delete[] grid[c];
		printf("h2\n");
	}
	delete[] grid;
}

Board::Board(int cols, int rows) :
		num_cols(cols), num_rows(rows) {
	grid = new char*[num_cols];
	for (int c = 0; c < num_cols; c++) {
		grid[c] = new char[num_rows];
		for (int r = 0; r < num_rows; r++) {
			grid[c][r] = EMPTY;
		}
	}
}

Board::Board(const Board& other) {
	num_cols = other.num_cols;
	num_rows = other.num_rows;
	grid = new char*[num_cols];
	for (int c = 0; c < num_cols; c++) {
		grid[c] = new char[num_rows];
		for (int r = 0; r < num_rows; r++) {
			grid[c][r] = other.grid[c][r];
		}
	}
}

Board& Board::operator=(const Board& rhs) {
	fflush(stdout);
	if (this == &rhs) {
		return *this;
	} else {
	//	printf("1\n");
		num_cols = rhs.num_cols;
	//	printf("2\n");
		num_rows = rhs.num_rows;
	//	printf("3\n");
	//	if (grid != NULL) {
	//		delete_grid();
	//	}
	//	printf("5\n");
		grid = new char*[num_cols];
	//	printf("6\n");
		for (int c = 0; c < num_cols; c++) {
	//		printf("7\n");
			grid[c] = new char[num_rows];
	//		printf("8\n");
			for (int r = 0; r < num_rows; r++) {
	//			printf("9\n");
				grid[c][r] = rhs.grid[c][r];
	//			printf("10\n");
			}
	//		printf("11\n");
		}
	//	printf("12\n");
		return *this;
	}
	//printf("13\n");
}

Board::~Board() {
	delete_grid();
}

char Board::get_cell(int col, int row) const {
	assert((col >= 0) && (col < num_cols));
	assert((row >= 0) && (row < num_rows));
	return grid[col][row];
}

void Board::set_cell(int col, int row, char val) {
	assert((col >= 0) && (col < num_cols));
	assert((row >= 0) && (row < num_rows));
	grid[col][row] = val;
}

bool Board::is_cell_empty(int col, int row) const {
	if (grid[col][row] == EMPTY) {
		return true;
	} else {
		return false;
	}
}

bool Board::is_in_bounds(int col, int row) const {
	if ((col >= 0) && (col < num_cols) && (row >= 0) && (row < num_rows)) {
		return true;
	} else {
		return false;
	}
}

void Board::display() const {
	for (int r = get_num_rows() - 1; r >= 0; r--) {
		std::cout << r << ":| ";
		for (int c = 0; c < get_num_cols(); c++) {
			std::cout << get_cell(c, r) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "   -";
	for (int c = 0; c < get_num_cols(); c++) {
		std::cout << "--";
	}
	std::cout << "\n";
	std::cout << "    ";
	for (int c = 0; c < get_num_cols(); c++) {
		std::cout << c << " ";
	}
	std::cout << "\n\n";
}

