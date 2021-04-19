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

class GameManager final: public QObject, public GameField, public GameEntity {
    Q_OBJECT

public:
    GameManager(const GameView*, int, int);
    void start();
    void addEntity(GameEntity*);
    MoveBlocker firstBallMoveBlocker(GameEntity*, int, int);
    void setupInitialState(GameField*, bool) { }
    void onTimerTick(GameField*);
    void onMouseMoveLeft(GameField*);
    void onMouseMoveRight(GameField*);
    MoveBlocker ballMoveBlocker(GameEntity*, int, int);

public slots:
    void onGoal();

protected:
    void timerEvent(QTimerEvent *event);
    QRect initialEntityRect(GameField*) { return QRect(0, 0, 0, 0); };
    void drawEntity() { };

private:
    void resetGame();
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
