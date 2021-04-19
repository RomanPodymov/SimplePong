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

class GameManager;

class GameEntity {

public:
    GameEntity(QRect, int);
    virtual void setupInitialState(GameManager*, bool) = 0;
    virtual void onTimerTick(GameManager*) = 0;
    virtual void onMouseMoveLeft(GameManager*) = 0;
    virtual void onMouseMoveRight(GameManager*) = 0;
    virtual MoveBlocker ballMoveBlocker(const GameEntity* const, int, int) const = 0;
    virtual void onGameReset(GameManager*);

protected:
    virtual QRect initialEntityRect(GameManager*) const = 0;
    virtual void drawEntity() = 0;
    QRect nextEntityRect(int, int) const;

public:
    QRect entityRect;

protected:
    const int stepSize;
};

#endif // GAMEENTITY_H
