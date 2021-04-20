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

class Ball final: public QObject, public QGraphicsRectItem, public GameEntity {
    Q_OBJECT

    enum MoveDirection { rightUp, rightDown, leftDown, leftUp };

public:
    Ball(QRect, int);
    void setupInitialState(GameManager*, bool);
    void onTimerTick(GameManager*);
    void onMouseMoveLeft(GameManager*) { };
    void onMouseMoveRight(GameManager*) { };
    MoveBlocker ballMoveBlocker(const GameEntity* const, int, int) const { return MoveBlocker::none; }

signals:
   void goal();

protected:
    QRect initialEntityRect(GameManager*) const;
    void drawEntity();

private:
    static MoveDirection randomDirection();
    std::tuple<int, int> getDxDy() const;
    MoveBlocker moveBlocker(GameManager*) const;
    MoveDirection nextMoveDirection(MoveBlocker) const;

private:
    MoveDirection currentMoveDirection;
};

#endif // BALL_H
