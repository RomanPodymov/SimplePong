//
//  ball.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "ball.h"
#include "gamemanager.h"
#include <QBrush>
#include <QRandomGenerator>

Ball::Ball(QRect entityRect, int stepSize): GameEntity(entityRect, stepSize) {

}

void Ball::setupInitialState(GameManager* gameManager, bool firstTime) {
    if (firstTime) {
        QObject::connect(this, SIGNAL(goal(bool)), gameManager, SLOT(onGoal(bool)));
    }
    currentMoveDirection = Ball::randomDirection();
    GameEntity::setupInitialState(gameManager, firstTime);
}

void Ball::onTimerTick(GameManager* gameManager) {
    const auto moveBlockerValue = moveBlocker(gameManager);
    if (moveBlockerValue) {
        if (moveBlockerValue == MoveBlocker::bottomWall) {
            emit goal(true);
            return;
        } else if (moveBlockerValue == MoveBlocker::topWall) {
            emit goal(false);
            return;
        } else {
            currentMoveDirection = nextMoveDirection(moveBlockerValue.value());
        }
    }
    const auto dXdY = getDxDy();
    entityRect = nextEntityRect(std::get<0>(dXdY), std::get<1>(dXdY));
    drawEntity();
}

std::optional<int> Ball::expectedBallAndOpponentContactX(GameManager*) const {
    switch (currentMoveDirection) {
        case MoveDirection::rightUp: {
            double stepsExpected = entityRect.y() / stepSize;
            return entityRect.x() + stepsExpected * stepSize;
        }

        case MoveDirection::rightDown: {
            return std::nullopt;
        }

        case MoveDirection::leftDown: {
            return std::nullopt;
        }

        case MoveDirection::leftUp: {
            double stepsExpected = entityRect.y() / stepSize;
            return entityRect.x() - stepsExpected * stepSize;
        }
    }
}


QRect Ball::initialEntityRect(GameManager* gameManager) const {
    return QRect(
        (gameManager->gameFieldColumns() - entityRect.size().width())/2,
        (gameManager->gameFieldRows() - entityRect.size().height())/2,
        entityRect.size().width(),
        entityRect.size().height()
    );
}

void Ball::drawEntity() {
    QBrush brush(Qt::yellow);
    setBrush(brush);
    setRect(entityRect);
}

Ball::MoveDirection Ball::randomDirection() {
    return MoveDirection(QRandomGenerator::global()->generate() % 4);
}

std::tuple<int, int> Ball::getDxDy() const {
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

std::optional<MoveBlocker> Ball::moveBlocker(GameManager* gameManager) const {
    const auto dXdY = getDxDy();
    const auto nextX = entityRect.x() + std::get<0>(dXdY);
    const auto nextY = entityRect.y() + std::get<1>(dXdY);
    return gameManager->firstBallMoveBlocker(this, nextX, nextY);
}

Ball::MoveDirection Ball::nextMoveDirection(MoveBlocker moveBlocker) const {
    switch (currentMoveDirection) {
        case MoveDirection::rightUp: {
            if (moveBlocker == MoveBlocker::topWall || moveBlocker == MoveBlocker::paddleOpponent) {
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
            if (moveBlocker == MoveBlocker::topWall || moveBlocker == MoveBlocker::paddleOpponent) {
                return MoveDirection::leftDown;
            } else {
                return MoveDirection::rightUp;
            }
        }
    }
}
