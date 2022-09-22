//
// Created by USER on 14.09.2022.
//

#ifndef OSISP1_SPRITE_H
#define OSISP1_SPRITE_H


class Sprite {
public:
    int x;
    int y;
    int width = 100;
    int height = 100;
    const int SPEED = 25;

    void moveUp(LONG topBound) {
        y - SPEED < topBound ? (y = SPEED) : (y -= SPEED);
    }

    void moveDown(LONG downBound) {
        y + height + SPEED > downBound ? (y = downBound - height - SPEED) : (y += SPEED);
    }

    void moveRight(LONG rightBound) {
        x + width + SPEED > rightBound ? (x = rightBound - width - SPEED) : (x += SPEED);
    }
    
    void moveLeft(LONG leftBound) {
        x - SPEED < leftBound ? (x = SPEED) : (x -= SPEED);
    }
};


#endif //OSISP1_SPRITE_H
