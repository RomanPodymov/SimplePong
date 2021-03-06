//
//  paddleopponent.h
//  App
//
//  Created by Roman Podymov on 20/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef PADDLEOPPONENT_H
#define PADDLEOPPONENT_H

#include "paddle.h"

class PaddleOpponent final: public Paddle {

    enum MoveDirection { left, right };

public:
    PaddleOpponent(QRect, int);
    void setupInitialState(GameManager*, bool);
    void onTimerTick(GameManager*);
    void onMouseMoveLeft(GameManager*) { };
    void onMouseMoveRight(GameManager*) { };
    std::optional<MoveBlocker> ballMoveBlocker(const GameEntity* const, int, int) const;
    std::optional<int> expectedBallAndOpponentContactX(GameManager*) const { return std::nullopt; }

protected:
    QRect initialEntityRect(GameManager*) const;
    void drawEntity();
};

#endif // PADDLEOPPONENT_H
