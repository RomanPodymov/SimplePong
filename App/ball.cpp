//
//  ball.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "ball.h"
#include "gamemanager.h"
#include <QPen>
#include <QRandomGenerator>

Ball::Ball(QRect entityRect, int stepSize): GameEntity(entityRect, stepSize) {

}

void Ball::setupInitialState(GameField* field, bool firstTime) {
    if (firstTime) {
        const auto gameManager = static_cast<GameManager*>(field);
        QObject::connect(this, SIGNAL(goal()), gameManager, SLOT(onGoal()));
    }
    currentMoveDirection = Ball::randomDirection();
    entityRect = initialEntityRect(field);
    drawEntity();
}

void Ball::onTimerTick(GameField* field) {
    const auto moveBlockerValue = moveBlocker(field);
    if (moveBlockerValue == MoveBlocker::bottomWall) {
        emit goal();
        return;
    } else if (moveBlockerValue != MoveBlocker::none) {
        currentMoveDirection = nextMoveDirection(moveBlockerValue);
    }
    const auto dXdY = getDxDy();
    entityRect = nextEntityRect(std::get<0>(dXdY), std::get<1>(dXdY));
    drawEntity();
}

void Ball::onMouseMoveLeft(GameField*) {

}

void Ball::onMouseMoveRight(GameField*) {

}

QRect Ball::initialEntityRect(GameField* field) {
    return QRect(
        (field->gameFieldColumns - entityRect.size().width())/2,
        (field->gameFieldRows - entityRect.size().height())/2,
        entityRect.size().width(),
        entityRect.size().height()
    );
}

void Ball::drawEntity() {
    QPen pen(Qt::yellow, 3);
    setPen(pen);
    setRect(entityRect.x(), entityRect.y(), entityRect.width(), entityRect.height());
}

MoveDirection Ball::randomDirection() {
    return MoveDirection(QRandomGenerator::global()->generate() % 4);
}

std::tuple<int, int> Ball::getDxDy() {
    switch (currentMoveDirection) {
        case MoveDirection::rightUp: {
            return std::tuple<int, int>(stepSize, -stepSize);
        }

        case MoveDirection::rightDown: {
            return std::tuple<int, int>(stepSize, stepSize);
        }

        case MoveDirection::leftDown: {
            return std::tuple<int, int>(-stepSize, stepSize);
        }

        case MoveDirection::leftUp: {
            return std::tuple<int, int>(-stepSize, -stepSize);
        }
    }
}

MoveBlocker Ball::moveBlocker(GameField* field) {
    const auto dXdY = getDxDy();
    const auto nextX = entityRect.x() + std::get<0>(dXdY);
    const auto nextY = entityRect.y() + std::get<1>(dXdY);
    const auto gameManager = static_cast<GameManager*>(field);
    const auto blocker = gameManager->firstBallMoveBlocker(this, nextX, nextY);
    if (blocker != MoveBlocker::none) {
        return blocker;
    } else if (nextX < 0) {
        return MoveBlocker::leftWall;
    } else if (nextY < 0) {
        return MoveBlocker::topWall;
    } else if (nextX + entityRect.width() > field->gameFieldColumns) {
        return MoveBlocker::rightWall;
    } else if (nextY + entityRect.height() > field->gameFieldRows) {
        return MoveBlocker::bottomWall;
    } else {
        return MoveBlocker::none;
    }
}

MoveDirection Ball::nextMoveDirection(MoveBlocker moveBlocker) {
    switch (currentMoveDirection) {
        case MoveDirection::rightUp: {
            if (moveBlocker == MoveBlocker::topWall) {
                return MoveDirection::rightDown;
            } else {
                return MoveDirection::leftUp;
            }
        }

        case MoveDirection::rightDown: {
            if (moveBlocker == MoveBlocker::bottomWall || moveBlocker == MoveBlocker::paddle) {
                return MoveDirection::rightUp;
            } else {
                return MoveDirection::leftDown;
            }
        }

        case MoveDirection::leftDown: {
            if (moveBlocker == MoveBlocker::bottomWall || moveBlocker == MoveBlocker::paddle) {
                return MoveDirection::leftUp;
            } else {
                return MoveDirection::rightDown;
            }
        }

        case MoveDirection::leftUp: {
            if (moveBlocker == MoveBlocker::topWall) {
                return MoveDirection::leftDown;
            } else {
                return MoveDirection::rightUp;
            }
        }
    }
}
