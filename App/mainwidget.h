//
//  mainwidget.h
//  App
//
//  Created by Roman Podymov on 27/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ball.h"
#include "gamemanager.h"
#include "gameview.h"
#include "paddle.h"
#include "paddleopponent.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class MainWidget final: public QWidget {
    Q_OBJECT

public:
    MainWidget(QSize screenSize = QSize(640, 480), QWidget *parent = nullptr);
    ~MainWidget();
    void resumeGame();
    void pauseGame();

public slots:
    void onGoal(bool);

private:
    void setupGameManager(QSize);

private:
    QPointer<QGraphicsScene> scene;
    QPointer<GameView> gameView;
    QPointer<GameManager> gameManager;
    Paddle* paddle;
    QPointer<Ball> ball;
    PaddleOpponent* paddleOpponent;
    QPointer<QHBoxLayout> customLayout;
    QPointer<QVBoxLayout> informationLayout;
    QPointer<QPushButton> buttonPauseResume;
    QPointer<QLabel> scorePaddle;
    QPointer<QLabel> scorePaddleOpponent;
};

#endif // MAINWIDGET_H
