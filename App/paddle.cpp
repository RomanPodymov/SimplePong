//
//  paddle.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "paddle.h"
#include <QPen>

Paddle::Paddle(QRect entityRect, int stepSize): GameEntity(entityRect, stepSize) {

}

void Paddle::setupInitialState(GameField* field, bool) {
    entityRect = initialEntityRect(field);
    drawEntity();
}

void Paddle::onMouseMoveLeft(GameField* field) {
    onMouseMove(field, -1, &Paddle::canMoveLeft);
}

void Paddle::onMouseMoveRight(GameField* field) {
    onMouseMove(field, 1, &Paddle::canMoveRight);
}

MoveBlocker Paddle::ballMoveBlocker(GameEntity* ball, int nextX, int nextY) {
    if (nextY + ball->entityRect.height() > entityRect.y() && nextX > entityRect.x() && nextX + ball->entityRect.width() < entityRect.right()) {
        return MoveBlocker::paddle;
    }
    return MoveBlocker::none;
}

QRect Paddle::initialEntityRect(GameField* field) {
    return QRect(
        (field->gameFieldColumns - entityRect.size().width())/2,
        field->gameFieldRows - entityRect.size().height(),
        entityRect.size().width(),
        entityRect.size().height()
    );
}

void Paddle::drawEntity() {
    QPen pen(Qt::green, 3);
    setPen(pen);
    setRect(entityRect.x(), entityRect.y(), entityRect.width(), entityRect.height());
}

void Paddle::onMouseMove(GameField* field, int stepSizeSign, bool(Paddle::*canMove)(const GameField* const)) {
    if (!(std::invoke(canMove, this, field))) {
        return;
    }
    entityRect = nextEntityRect(stepSize * stepSizeSign, 0);
    drawEntity();
}

bool Paddle::canMoveLeft(const GameField* const) {
    return entityRect.x() - stepSize >= 0;
}

bool Paddle::canMoveRight(const GameField* const field) {
    return entityRect.right() + stepSize <= field->gameFieldColumns;
}
