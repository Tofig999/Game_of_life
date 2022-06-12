#include "Table.h"

Table::Table() {
    rows = ROWS;
    cols = COLS;

    grid = new int*[rows];
    for (int i = 0; i < rows; i++)
        grid[i] = new int[COLS]{};
}

Table::Table(const Table &table) {
    rows = table.rows;
    cols = table.cols;

    grid = new int*[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[COLS]{};
        for (int j = 0; j < cols; j++)
            grid[i][j] = table.grid[i][j];
    }
}

Table::Table(Table &&table) {
    grid = table.grid;
    rows = table.rows;
    cols = table.cols;
}

void Table::operator=(const Table &table) {
    if (grid != nullptr) {
        for (int i = 0; i < rows; i++)
            delete[] grid[i];
        delete[] grid;
    }

    rows = table.rows;
    cols = table.cols;

    grid = new int*[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new int[COLS]{};
        for (int j = 0; j < cols; j++)
            grid[i][j] = table.grid[i][j];
    }
}

void Table::fillRandomly() {
    std::srand(std::time(nullptr));

    for (int i = 0; i < RANDOM_COUNT; i++) {
        int row = std::rand() % rows;
        int col = std::rand() % cols;

        setCellState(row, col, 1);
    }
}

Table Table::getNextState() const {
    Table table{};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int state = getCellState(i, j);

            size_t count = getNeighboursCount(i, j);

            if (state == 1 && (count < 2 || count > 3))
                table.setCellState(i, j, 0);
            else if (state == 0 && count == 3)
                table.setCellState(i, j, 1);
            else
                table.setCellState(i, j, state);
        }
    }

    return table;
}

const int Table::getCellState(size_t row, size_t col) const {
    if (row >= rows || col >= cols)
        throw InvalidPositionException{};

    return grid[row][col];
}

void Table::setCellState(size_t row, size_t col, int state) {
    if (row >= rows || col >= cols)
        throw InvalidPositionException{};

    grid[row][col] = state;
}

size_t Table::getNeighboursCount(size_t row, size_t col) const {
    if (row >= rows || col >= cols)
        throw InvalidPositionException{};

    size_t counter = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;

            int newRow = (row + i + rows) % rows;
            int newCol = (col + j + cols) % cols;

            try {
                if (this->getCellState(newRow, newCol) != 0)
                    counter++;
            } catch (InvalidPositionException &ex) {
                // std::cout << ex.what() << std::endl;
            }
        }
    }

    return counter;
}

void Table::draw() const {
    std::cout << '+';
    for (int i = 0; i < cols; i++)
        std::cout << '-';
    std::cout << '+' << std::endl;

    for (int i = 0; i < rows; i++) {
        std::cout << '|';
        for (int j = 0; j < cols; j++)
            std::cout << (grid[i][j] == 1 ? "*" : " ");
        std::cout << '|' << std::endl;
    }

    std::cout << '+';
    for (int i = 0; i < cols; i++)
        std::cout << '-';
    std::cout << '+' << std::endl;
}

Table::~Table() {
    for (int i = 0; i < rows; i++)
        delete[] grid[i];
    delete[] grid;

    rows = 0;
    cols = 0;
}
