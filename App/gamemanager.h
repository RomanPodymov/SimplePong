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

class GameManager final: public QObject, public GameEntity {
    Q_OBJECT

public:
    GameManager(const GameView*, int, int);
    void start();
    void addEntity(GameEntity*);
    MoveBlocker firstBallMoveBlocker(const GameEntity* const, int, int) const;
    void setupInitialState(GameManager*, bool) { }
    void onTimerTick(GameManager*);
    void onMouseMoveLeft(GameManager*);
    void onMouseMoveRight(GameManager*);
    MoveBlocker ballMoveBlocker(const GameEntity* const, int, int) const;
    void onGameReset(GameManager*);
    int gameFieldColumns() const { return entityRect.width(); }
    int gameFieldRows() const { return entityRect.height(); }

public slots:
    void onGoal();

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
};

#endif // GAMEMANAGER_H
