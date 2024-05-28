//
// Created by zalyg on 27.05.2024.
//

#ifndef GAME2048_GAME_H
#define GAME2048_GAME_H


class Game {
private:
    int board[4][4];
    int score = 0;

    void addTile();
    void compress(int row[4]);
    void merge(int row[4]);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveUp();
    bool canMoveDown();
    bool canMove(int direction);
    void move(int direction);
    void printBoard();

public:
    Game();
    void play();
};


#endif //GAME2048_GAME_H
