#pragma once

#include <iostream>
#include <cstdlib>
#include "Exceptions.h"

#define ROWS 20
#define COLS ROWS
#define RANDOM_COUNT 50

class Table {
private:
    int **grid;
    size_t rows;
    size_t cols;
public:
    Table();

    Table(const Table &table);

    Table(Table &&table);

    void operator=(const Table &table);

    void fillRandomly();

    Table getNextState() const;

    const int getCellState(size_t row, size_t col) const;

    void setCellState(size_t row, size_t col, int state);

    size_t getNeighboursCount(size_t row, size_t col) const;

    void draw() const;

    ~Table();
};
