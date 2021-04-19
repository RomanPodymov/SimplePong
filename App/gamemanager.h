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
#include "gamefield.h"
#include "gameview.h"
#include <QObject>
#include <QVarLengthArray>
#include <QPointer>

class GameManager final: public QObject, public GameField {
    Q_OBJECT

public:
    GameManager(const GameView*, int, int);
    void start();
    void addEntity(GameEntity*);
    MoveBlocker firstBallMoveBlocker(const GameEntity* const, int, int) const;
    void setupInitialState(GameField*, bool) { }
    void onTimerTick(GameField*);
    void onMouseMoveLeft(GameField*);
    void onMouseMoveRight(GameField*);
    MoveBlocker ballMoveBlocker(const GameEntity* const, int, int) const;
    void onGameReset(GameField*);

public slots:
    void onGoal();

protected:
    void timerEvent(QTimerEvent *event);
    QRect initialEntityRect(GameField*) const { return entityRect; };
    void drawEntity() { };

private:
    void forAllEntities(GameField*, void(GameEntity::*)(GameField*));

private slots:
    void onMouseMoveLeft();
    void onMouseMoveRight();

private:
    const QPointer<const GameView> gameView;
    int eventsTimerId;
    QVarLengthArray<GameEntity*> entities;
};

#endif // GAMEMANAGER_H
