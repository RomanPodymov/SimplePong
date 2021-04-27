//
//  paddle.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "paddle.h"
#include "gamemanager.h"
#include <QBrush>

Paddle::Paddle(QRect entityRect, int stepSize): GameEntity(entityRect, stepSize) {

}

void Paddle::setupInitialState(GameManager* gameManager, bool firstTime) {
    GameEntity::setupInitialState(gameManager, firstTime);
}

void Paddle::onMouseMoveLeft(GameManager* gameManager) {
    onMouseMove(gameManager, -1, &Paddle::canMoveLeft);
}

void Paddle::onMouseMoveRight(GameManager* gameManager) {
    onMouseMove(gameManager, 1, &Paddle::canMoveRight);
}

std::optional<MoveBlocker> Paddle::ballMoveBlocker(const GameEntity* const ball, int nextX, int nextY) const {
    if (nextY + ball->entityRect.height() > entityRect.y() &&
        nextX > entityRect.x() - ball->entityRect.width() &&
        nextX < entityRect.right()) {
        return MoveBlocker::paddle;
    }
    return std::nullopt;
}

QRect Paddle::initialEntityRect(GameManager* gameManager) const {
    return QRect(
        (gameManager->gameFieldColumns() - entityRect.size().width())/2,
        gameManager->gameFieldRows() - entityRect.size().height(),
        entityRect.size().width(),
        entityRect.size().height()
    );
}

void Paddle::drawEntity() {
    QBrush brush(Qt::green);
    setBrush(brush);
    setRect(entityRect);
}

void Paddle::onMouseMove(GameManager* gameManager, int stepSizeSign, bool(Paddle::*canMove)(const GameManager* const)) {
    if (!(std::invoke(canMove, this, gameManager))) {
        return;
    }
    entityRect = nextEntityRect(stepSize * stepSizeSign, 0);
    drawEntity();
}

bool Paddle::canMoveLeft(const GameManager* const) {
    return entityRect.x() - stepSize >= 0;
}

bool Paddle::canMoveRight(const GameManager* const gameManager) {
    return entityRect.right() + stepSize <= gameManager->gameFieldColumns();
}
