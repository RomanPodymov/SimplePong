//
//  gamemanager.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "gamemanager.h"
#include "mainwidget.h"

GameManager::GameManager(const GameView* gameView, int gameFieldRows, int gameFieldColumns): GameEntity(QRect(0, 0, gameFieldColumns, gameFieldRows), 0),
    gameView(gameView),
    isPaused(false),
    scorePaddle(0),
    scorePaddleOpponent(0) {

}

void GameManager::pauseResumeGame(MainWidget* mainWidget) {
    if (isPaused) {
        resumeGame(mainWidget);
    } else {
        pauseGame(mainWidget);
    }
    isPaused = !isPaused;
}

void GameManager::resumeGame(MainWidget* mainWidget) {
    mainWidget->resumeGame();
    eventsTimerId = startTimer(40, Qt::TimerType::PreciseTimer);
    QObject::connect(gameView, SIGNAL(mouseMoveLeft()), this, SLOT(onMouseMoveLeft()));
    QObject::connect(gameView, SIGNAL(mouseMoveRight()), this, SLOT(onMouseMoveRight()));
}

void GameManager::pauseGame(MainWidget* mainWidget) {
    mainWidget->pauseGame();
    killTimer(eventsTimerId);
    QObject::disconnect(gameView, SIGNAL(mouseMoveLeft()), this, SLOT(onMouseMoveLeft()));
    QObject::disconnect(gameView, SIGNAL(mouseMoveRight()), this, SLOT(onMouseMoveRight()));
}

void GameManager::addEntity(GameEntity* entity) {
    entities.append(entity);
    entity->setupInitialState(this, true);
}

std::optional<MoveBlocker> GameManager::firstBallMoveBlocker(const GameEntity* const ball, int nextX, int nextY) const {
    for (const auto& entity : entities) {
        const auto blocker = entity->ballMoveBlocker(ball, nextX, nextY);
        if (blocker) {
            return blocker;
        }
    }
    return std::nullopt;
}

void GameManager::onTimerTick(GameManager* gameManager) {
    forAllEntities(gameManager, &GameEntity::onTimerTick);
}

void GameManager::onMouseMoveLeft(GameManager* gameManager) {
    forAllEntities(gameManager, &GameEntity::onMouseMoveLeft);
}

void GameManager::onMouseMoveRight(GameManager* gameManager) {
    forAllEntities(gameManager, &GameEntity::onMouseMoveRight);
}

std::optional<MoveBlocker> GameManager::ballMoveBlocker(const GameEntity* const ball, int nextX, int nextY) const {
    if (nextX < 0) {
        return MoveBlocker::leftWall;
    } else if (nextY < 0) {
        return MoveBlocker::topWall;
    } else if (nextX + ball->entityRect.width() > gameFieldColumns()) {
        return MoveBlocker::rightWall;
    } else if (nextY + ball->entityRect.height() > gameFieldRows()) {
        return MoveBlocker::bottomWall;
    } else {
        return std::nullopt;
    }
}

std::optional<int> GameManager::expectedBallAndOpponentContactX(GameManager* gameManager) const {
    for (const auto& entity : entities) {
        if (entity != gameManager) {
            const auto expectedBallAndOpponentContactXValue = entity->expectedBallAndOpponentContactX(gameManager);
            if (expectedBallAndOpponentContactXValue) {
               return expectedBallAndOpponentContactXValue;
            }
        }
    }
    return std::nullopt;
}

void GameManager::updateScorePaddleLabel(QPointer<QLabel> label, bool shouldIncrementValue) {
    if (shouldIncrementValue) {
        scorePaddle++;
    }
    label->setText(QString::number(scorePaddle));
}

void GameManager::updateScorePaddleOpponent(QPointer<QLabel> label, bool shouldIncrementValue) {
    if (shouldIncrementValue) {
        scorePaddleOpponent++;
    }
    label->setText(QString::number(scorePaddleOpponent));
}

void GameManager::onGoal(bool) {
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

void GameManager::onGameReset(GameManager* gameManager) {
    forAllEntities(gameManager, &GameEntity::onGameReset);
}

void GameManager::forAllEntities(GameManager* gameManager, void(GameEntity::*functionToCall)(GameManager*)) {
    for (const auto& entity : entities) {
        if (entity != this) {
            std::invoke(functionToCall, entity, gameManager);
        }
    }
}
