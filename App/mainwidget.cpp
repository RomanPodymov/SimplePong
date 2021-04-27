//
//  mainwidget.cpp
//  App
//
//  Created by Roman Podymov on 27/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "mainwidget.h"

MainWidget::MainWidget(QSize screenSize, QWidget *parent): QWidget(parent) {
    scene = new QGraphicsScene(0, 0, screenSize.width(), screenSize.height());

    customLayout = new QHBoxLayout();

    gameView = new GameView(scene);
    customLayout->addWidget(gameView);

    informationLayout = new QVBoxLayout();
    customLayout->addLayout(informationLayout);

    scorePaddleOpponent = new QLabel;
    scorePaddleOpponent->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    informationLayout->addWidget(scorePaddleOpponent);

    buttonPauseResume = new QPushButton;
    QObject::connect(buttonPauseResume, &QPushButton::pressed, [&]() {
        gameManager->pauseResumeGame(this);
    });
    informationLayout->addWidget(buttonPauseResume);

    scorePaddle = new QLabel;
    scorePaddle->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    informationLayout->addWidget(scorePaddle);

    setupGameManager(screenSize);

    setLayout(customLayout);

    gameView->setFixedSize(screenSize);
    gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    gameView->setFrameShape(QFrame::Shape::NoFrame);
}

MainWidget::~MainWidget() {
    delete buttonPauseResume;
    delete scorePaddleOpponent;
    delete scorePaddle;
    delete gameManager;
    delete paddleOpponent;
    delete ball;
    delete paddle;
    delete gameView;
    delete scene;
    delete customLayout;
    delete informationLayout;
}

void MainWidget::resumeGame() {
    buttonPauseResume->setText(MainWidget::tr("Pause"));
}

void MainWidget::pauseGame() {
    buttonPauseResume->setText(MainWidget::tr("Resume"));
}

void MainWidget::onGoal(bool toOpponent) {
    gameManager->updateScorePaddleLabel(scorePaddle, toOpponent);
    gameManager->updateScorePaddleOpponent(scorePaddleOpponent, !toOpponent);
}

void MainWidget::setupGameManager(QSize screenSize) {
    paddle = new Paddle(QRect(0, 0, 100, 20), 5);
    scene->addItem(paddle);

    ball = new Ball(QRect(0, 0, 10, 10), 5);
    QObject::connect(ball, SIGNAL(goal(bool)), this, SLOT(onGoal(bool)));
    scene->addItem(ball);

    paddleOpponent = new PaddleOpponent(QRect(0, 0, 100, 20), 5);
    scene->addItem(paddleOpponent);

    gameManager = new GameManager(gameView, screenSize.height(), screenSize.width());
    gameManager->addEntity(paddle);
    gameManager->addEntity(ball);
    gameManager->addEntity(paddleOpponent);
    gameManager->addEntity(gameManager);
    gameManager->resumeGame(this);
    gameManager->updateScorePaddleLabel(scorePaddle, false);
    gameManager->updateScorePaddleOpponent(scorePaddleOpponent, false);
}
