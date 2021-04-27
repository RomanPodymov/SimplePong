//
//  paddleopponent.cpp
//  App
//
//  Created by Roman Podymov on 20/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "paddleopponent.h"
#include "gamemanager.h"
#include <QBrush>

PaddleOpponent::PaddleOpponent(QRect entityRect, int stepSize): Paddle(entityRect, stepSize) {

}

void PaddleOpponent::setupInitialState(GameManager* gameManager, bool firstTime) {
    Paddle::setupInitialState(gameManager, firstTime);
}

void PaddleOpponent::onTimerTick(GameManager* gameManager) {
    const auto expectedBallAndOpponentContactXValue = gameManager->expectedBallAndOpponentContactX(gameManager);
    if (!expectedBallAndOpponentContactXValue) {
        return;
    }
    std::optional<MoveDirection> currentMoveDirection;
    if (expectedBallAndOpponentContactXValue < entityRect.x() + entityRect.width()/2) {
        currentMoveDirection = MoveDirection::left;
    } else if (expectedBallAndOpponentContactXValue > entityRect.x() + entityRect.width()/2) {
        currentMoveDirection = MoveDirection::right;
    } else {
        currentMoveDirection = std::nullopt;
    }
    if (currentMoveDirection == MoveDirection::left && !canMoveLeft(gameManager)) {
        currentMoveDirection = std::nullopt;
    } else if (currentMoveDirection == MoveDirection::right && !canMoveRight(gameManager)) {
        currentMoveDirection = std::nullopt;
    }
    if (currentMoveDirection == MoveDirection::left) {
        Paddle::onMouseMoveLeft(gameManager);
    } else if (currentMoveDirection == MoveDirection::right) {
        Paddle::onMouseMoveRight(gameManager);
    }
}

std::optional<MoveBlocker> PaddleOpponent::ballMoveBlocker(const GameEntity* const ball, int nextX, int nextY) const {
    if (nextY < entityRect.bottom() &&
        nextX > entityRect.x() - ball->entityRect.width() &&
        nextX < entityRect.right()) {
        return MoveBlocker::paddleOpponent;
    }
    return std::nullopt;
}

QRect PaddleOpponent::initialEntityRect(GameManager* gameManager) const {
    return QRect(
        (gameManager->gameFieldColumns() - entityRect.size().width())/2,
        0,
        entityRect.size().width(),
        entityRect.size().height()
    );
}

void PaddleOpponent::drawEntity() {
    QBrush brush(Qt::red);
    setBrush(brush);
    setRect(entityRect);
}
