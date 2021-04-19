//
//  gameentity.h
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <QRect>

enum MoveBlocker { none, rightWall, bottomWall, leftWall, topWall, paddle };

class GameField;

class GameEntity {

public:
    GameEntity(QRect, int);
    virtual void setupInitialState(GameField*, bool) = 0;
    virtual void onTimerTick(GameField*) = 0;
    virtual void onMouseMoveLeft(GameField*) = 0;
    virtual void onMouseMoveRight(GameField*) = 0;
    virtual MoveBlocker ballMoveBlocker(const GameEntity* const, int, int) const = 0;
    virtual void onGameReset(GameField*);

protected:
    virtual QRect initialEntityRect(GameField*) const = 0;
    virtual void drawEntity() = 0;
    QRect nextEntityRect(int, int) const;

public:
    QRect entityRect;

protected:
    const int stepSize;
};

#endif // GAMEENTITY_H
