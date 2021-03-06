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

class Paddle: public QGraphicsRectItem, public GameEntity {

public:
    Paddle(QRect, int);
    void setupInitialState(GameManager*, bool);
    void onTimerTick(GameManager*) { };
    void onMouseMoveLeft(GameManager*);
    void onMouseMoveRight(GameManager*);
    std::optional<MoveBlocker> ballMoveBlocker(const GameEntity* const, int, int) const;
    std::optional<int> expectedBallAndOpponentContactX(GameManager*) const { return std::nullopt; }

protected:
    QRect initialEntityRect(GameManager*) const;
    void drawEntity();
    bool canMoveLeft(const GameManager* const);
    bool canMoveRight(const GameManager* const);

private:
    void onMouseMove(GameManager* field, int, bool(Paddle::*)(const GameManager* const));
};

#endif // PADDLE_H
