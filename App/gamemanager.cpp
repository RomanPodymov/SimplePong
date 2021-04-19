//
//  gamemanager.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "gamemanager.h"

GameManager::GameManager(const GameView* gameView, int gameFieldRows, int gameFieldColumns): GameField(gameFieldRows, gameFieldColumns),
    gameView(gameView) {
    QObject::connect(gameView, SIGNAL(mouseMoveLeft()), this, SLOT(onMouseMoveLeft()));
    QObject::connect(gameView, SIGNAL(mouseMoveRight()), this, SLOT(onMouseMoveRight()));
}

void GameManager::start() {
    eventsTimerId = startTimer(40, Qt::TimerType::PreciseTimer);
}

void GameManager::addEntity(GameEntity* entity) {
    entities.append(entity);
    entity->setupInitialState(this, true);
}

MoveBlocker GameManager::firstBallMoveBlocker(const GameEntity* const ball, int nextX, int nextY) const {
    for (const auto& entity : entities) {
        const auto blocker = entity->ballMoveBlocker(ball, nextX, nextY);
        if (blocker != MoveBlocker::none) {
            return blocker;
        }
    }
    return MoveBlocker::none;
}

void GameManager::onTimerTick(GameField* field) {
    forAllEntities(field, &GameEntity::onTimerTick);
}

void GameManager::onMouseMoveLeft(GameField* field) {
    forAllEntities(field, &GameEntity::onMouseMoveLeft);
}

void GameManager::onMouseMoveRight(GameField* field) {
    forAllEntities(field, &GameEntity::onMouseMoveRight);
}

MoveBlocker GameManager::ballMoveBlocker(const GameEntity* const ball, int nextX, int nextY) const {
    if (nextX < 0) {
        return MoveBlocker::leftWall;
    } else if (nextY < 0) {
        return MoveBlocker::topWall;
    } else if (nextX + ball->entityRect.width() > gameFieldColumns()) {
        return MoveBlocker::rightWall;
    } else if (nextY + ball->entityRect.height() > gameFieldRows()) {
        return MoveBlocker::bottomWall;
    } else {
        return MoveBlocker::none;
    }
}

void GameManager::onGoal() {
    onGameReset(this);
}

void GameManager::timerEvent(QTimerEvent*) {
    onTimerTick(this);
}

void GameManager::onMouseMoveLeft() {
    onMouseMoveLeft(this);
}

void GameManager::onMouseMoveRight() {
    onMouseMoveRight(this);
}

void GameManager::onGameReset(GameField* field) {
    forAllEntities(field, &GameEntity::onGameReset);
}

void GameManager::forAllEntities(GameField* field, void(GameEntity::*functionToCall)(GameField*)) {
    for (const auto& entity : entities) {
        if (entity != this) {
            std::invoke(functionToCall, entity, field);
        }
    }
}
