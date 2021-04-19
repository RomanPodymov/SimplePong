//
//  paddle.h
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef PADDLE_H
#define PADDLE_H

#include "gameentity.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Paddle final: public QGraphicsRectItem, public GameEntity {

public:
    Paddle(QRect, int);
    void setupInitialState(GameField*, bool);
    void onTimerTick(GameField*) { };
    void onMouseMoveLeft(GameField*);
    void onMouseMoveRight(GameField*);
    MoveBlocker ballMoveBlocker(const GameEntity* const, int, int) const;

protected:
    QRect initialEntityRect(GameField*) const;
    void drawEntity();

private:
    void onMouseMove(GameField* field, int, bool(Paddle::*)(const GameField* const));
    bool canMoveLeft(const GameField* const);
    bool canMoveRight(const GameField* const);
};

#endif // PADDLE_H
