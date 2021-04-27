//
//  gamemanager.h
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "gameentity.h"
#include "gameview.h"
#include <QObject>
#include <QVarLengthArray>
#include <QPointer>
#include <QLabel>

class MainWidget;

class GameManager final: public QObject, public GameEntity {
    Q_OBJECT

public:
    GameManager(const GameView*, int, int);
    void pauseResumeGame(MainWidget*);
    void resumeGame(MainWidget*);
    void pauseGame(MainWidget*);
    void addEntity(GameEntity*);
    std::optional<MoveBlocker> firstBallMoveBlocker(const GameEntity* const, int, int) const;
    void setupInitialState(GameManager*, bool) { }
    void onTimerTick(GameManager*);
    void onMouseMoveLeft(GameManager*);
    void onMouseMoveRight(GameManager*);
    std::optional<MoveBlocker> ballMoveBlocker(const GameEntity* const, int, int) const;
    std::optional<int> expectedBallAndOpponentContactX(GameManager* gameManager) const;
    void onGameReset(GameManager*);
    int gameFieldColumns() const { return entityRect.width(); }
    int gameFieldRows() const { return entityRect.height(); }
    void updateScorePaddleLabel(QPointer<QLabel>);
    void updateScorePaddleOpponent(QPointer<QLabel>);

public slots:
    void onGoal(bool);

protected:
    void timerEvent(QTimerEvent *event);
    QRect initialEntityRect(GameManager*) const { return entityRect; };
    void drawEntity() { };

private:
    void forAllEntities(GameManager*, void(GameEntity::*)(GameManager*));

private slots:
    void onMouseMoveLeft();
    void onMouseMoveRight();

private:
    const QPointer<const GameView> gameView;
    int eventsTimerId;
    QVarLengthArray<GameEntity*> entities;
    bool isPaused;
    int scorePaddle;
    int scorePaddleOpponent;
};

#endif // GAMEMANAGER_H
