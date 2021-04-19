//
//  ball.h
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef BALL_H
#define BALL_H

#include "gameentity.h"
#include <QGraphicsRectItem>

enum MoveDirection { rightUp, rightDown, leftDown, leftUp };

class Ball final: public QObject, public QGraphicsRectItem, public GameEntity {
    Q_OBJECT

public:
    Ball(QRect, int);
    void setupInitialState(GameField*, bool);
    void onTimerTick(GameField*);
    void onMouseMoveLeft(GameField*) { };
    void onMouseMoveRight(GameField*) { };
    MoveBlocker ballMoveBlocker(GameEntity*, int, int) { return MoveBlocker::none; }

signals:
   void goal();

protected:
    QRect initialEntityRect(GameField*);
    void drawEntity();

private:
    static MoveDirection randomDirection();
    std::tuple<int, int> getDxDy();
    MoveBlocker moveBlocker(GameField*);
    MoveDirection nextMoveDirection(MoveBlocker);

private:
    MoveDirection currentMoveDirection;
};

#endif // BALL_H
