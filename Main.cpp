#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Table.h"

void clearConsole();

int main() {
    Table table{};
    table.fillRandomly();

    table.draw();

    while (1) {
        sleep(1);
        clearConsole();

        table = table.getNextState();
        table.draw();
    }
}

void clearConsole() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
