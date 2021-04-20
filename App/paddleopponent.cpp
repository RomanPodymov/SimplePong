//
//  paddleopponent.cpp
//  App
//
//  Created by Roman Podymov on 20/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "paddleopponent.h"
#include "gamemanager.h"
#include <QPen>
#include <QRandomGenerator>

PaddleOpponent::PaddleOpponent(QRect entityRect, int stepSize): Paddle(entityRect, stepSize) {

}

void PaddleOpponent::setupInitialState(GameManager* gameManager, bool firstTime) {
    currentMoveDirection = PaddleOpponent::randomDirection();
    Paddle::setupInitialState(gameManager, firstTime);
}

void PaddleOpponent::onTimerTick(GameManager* gameManager) {
    if (currentMoveDirection == MoveDirection::left && !canMoveLeft(gameManager)) {
        currentMoveDirection = MoveDirection::right;
    } else if (currentMoveDirection == MoveDirection::right && !canMoveRight(gameManager)) {
        currentMoveDirection = MoveDirection::left;
    }
    if (currentMoveDirection == MoveDirection::left) {
        Paddle::onMouseMoveLeft(gameManager);
    } else {
        Paddle::onMouseMoveRight(gameManager);
    }
}

MoveBlocker PaddleOpponent::ballMoveBlocker(const GameEntity* const ball, int nextX, int nextY) const {
    if (nextY < entityRect.bottom() &&
        nextX > entityRect.x() - ball->entityRect.width() &&
        nextX < entityRect.right()) {
        return MoveBlocker::paddleOpponent;
    }
    return MoveBlocker::none;
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
    QPen pen(Qt::red, 3);
    setPen(pen);
    setRect(entityRect);
}

PaddleOpponent::MoveDirection PaddleOpponent::randomDirection() {
    return MoveDirection(QRandomGenerator::global()->generate() % 2);
}
