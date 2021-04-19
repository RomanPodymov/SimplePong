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

MoveBlocker GameManager::firstBallMoveBlocker(GameEntity* ball, int nextX, int nextY) {
    foreach (const auto& entity, entities) {
        const auto blocker = entity->ballMoveBlocker(ball, nextX, nextY);
        if (blocker != MoveBlocker::none) {
            return blocker;
        }
    }
    return MoveBlocker::none;
}

void GameManager::onGoal() {
    resetGame();
}

void GameManager::timerEvent(QTimerEvent*) {
    foreach (const auto& entity, entities) {
        entity->onTimerTick(this);
    }
}

void GameManager::onMouseMoveLeft() {
    foreach (const auto& entity, entities) {
        entity->onMouseMoveLeft(this);
    }
}

void GameManager::onMouseMoveRight() {
    foreach (const auto& entity, entities) {
        entity->onMouseMoveRight(this);
    }
}

void GameManager::resetGame() {
    foreach (const auto& entity, entities) {
        entity->setupInitialState(this, false);
    }
}
