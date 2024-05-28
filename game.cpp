//
// Created by zalyg on 27.05.2024.
//

#include "game.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


Game::Game() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            board[i][j] = 0;
        }
    }

    srand(time(0));
    addTile();
    addTile();
}


void Game::addTile() {
    int emptyCells[16][2];
    int emptyCount = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) {
                emptyCells[emptyCount][0] = i;
                emptyCells[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }

    if (emptyCount == 0) return;

    int idx = rand() % emptyCount;
    int x = emptyCells[idx][0];
    int y = emptyCells[idx][1];
    board[x][y] = (rand() % 10 == 0) ? 4 : 2;
}

void Game::compress(int row[4]) {
    int newRow[4] = {0, 0, 0, 0};
    int pos = 0;
    for (int i = 0; i < 4; ++i) {
        if (row[i] != 0) {
            newRow[pos++] = row[i];
        }
    }
    for (int i = 0; i < 4; ++i) {
        row[i] = newRow[i];
    }
}

void Game::merge(int row[4]) {
    for (int i = 0; i < 3; ++i) {
        if (row[i] == row[i + 1] && row[i] != 0) {
            row[i] *= 2;
            score += row[i];
            row[i + 1] = 0;
        }
    }
}


void Game::moveLeft() {
    for (int i = 0; i < 4; ++i) {
        compress(board[i]);
        merge(board[i]);
        compress(board[i]);
    }
}

void Game::moveRight() {
    for (int i = 0; i < 4; ++i) {
        int reversedRow[4] = {board[i][3], board[i][2], board[i][1], board[i][0]};
        compress(reversedRow);
        merge(reversedRow);
        compress(reversedRow);
        for (int j = 0; j < 4; ++j) {
            board[i][3 - j] = reversedRow[j];
        }
    }
}

void Game::moveUp() {
    for (int j = 0; j < 4; ++j) {
        int column[4];
        for (int i = 0; i < 4; ++i) {
            column[i] = board[i][j];
        }
        compress(column);
        merge(column);
        compress(column);
        for (int i = 0; i < 4; ++i) {
            board[i][j] = column[i];
        }
    }
}

void Game::moveDown() {
    for (int j = 0; j < 4; ++j) {
        int column[4];
        for (int i = 0; i < 4; ++i) {
            column[i] = board[i][j];
        }
        int reversedColumn[4] = {column[3], column[2], column[1], column[0]};
        compress(reversedColumn);
        merge(reversedColumn);
        compress(reversedColumn);
        for (int i = 0; i < 4; ++i) {
            board[3 - i][j] = reversedColumn[i];
        }
    }
}

bool Game::canMoveLeft() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            if (board[i][j] != 0 && (board[i][j - 1] == 0 || board[i][j - 1] == board[i][j])) {
                return true;
            }
        }
    }
    return false;
}
bool Game::canMoveRight() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 2; j >= 0; --j) {  // Начинаем с 2, так как будем сравнивать с последующей плиткой
            if (board[i][j] != 0 && (board[i][j + 1] == 0 || board[i][j + 1] == board[i][j])) {
                return true;
            }
        }
    }
    return false;
}
bool Game::canMoveUp() {
    for (int j = 0; j < 4; ++j) {
        for (int i = 1; i < 4; ++i) {  // Начинаем с 1, так как будем сравнивать с предыдущей плиткой
            if (board[i][j] != 0 && (board[i - 1][j] == 0 || board[i - 1][j] == board[i][j])) {
                return true;
            }
        }
    }
    return false;
}
bool Game::canMoveDown() {
    for (int j = 0; j < 4; ++j) {
        for (int i = 2; i >= 0; --i) {  // Начинаем с 2, так как будем сравнивать с последующей плиткой
            if (board[i][j] != 0 && (board[i + 1][j] == 0 || board[i + 1][j] == board[i][j])) {
                return true;
            }
        }
    }
    return false;
}

//bool Game::canMove(int direction) {
//    if (direction == 0) {
//        return canMoveLeft();
//    } else if (direction == 1) {
//        return canMoveRight();
//    } else if (direction == 2) {
//        return canMoveUp();
//    } else if (direction == 3) {
//        return canMoveDown();
//    }
//    return false;
//}

//void Game::move(int direction) {
//    if (direction == 0) {
//        moveLeft();
//    } else if (direction == 1) {
//        moveRight();
//    } else if (direction == 2) {
//        moveUp();
//    } else if (direction == 3) {
//        moveDown();
//    }
//
//    addTile();  // Добавляем новую плитку после успешного хода
//}



void Game::printBoard() {
    cout << "Score: " << score << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}


void Game::play() {
    char direction;
    bool moved = false;

    while (true) {
        printBoard();  // Отображаем текущее состояние игрового поля
        std::cout << "Enter move (w, s, a, d, q): ";
        std::cin >> direction;

        switch (direction) {
            case 'a':
                moved = canMoveLeft();
                if (moved){
                    moveLeft();
                    addTile();
                }
                break;
            case 'd':
                moved = canMoveRight();
                if (moved){
                    moveRight();
                    addTile();
                }
                break;
            case 'w':
                moved = canMoveUp();
                if (moved) {
                    moveUp();
                    addTile();
                }
                break;
            case 's':
                moved = canMoveDown();
                if (moved) {
                    moveDown();
                    addTile();
                }
                break;

            case 'q':
                cout << "Exit" << endl;
                return;
            default:
                cout << "Invalid input. Please enter w, s, a, d, or q." << endl;
                continue;
        }

        if (!moved) {
            cout << "Move not possible in that direction." << endl;
            continue;
        }

        // Проверка, можно ли сделать ход
        if (!canMoveLeft() && !canMoveRight() && !canMoveUp() && !canMoveDown()) {
            printBoard();
            cout << "Game over! No more moves possible." << endl;
            break;
        }
    }
}

