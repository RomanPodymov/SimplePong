//
//  main.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "gamemanager.h"
#include "gameview.h"
#include "ball.h"
#include "paddle.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QSize screenSize(640, 480);
    QGraphicsScene scene(0, 0, screenSize.width(), screenSize.height());

    Paddle paddle(QRect(0, 0, 100, 20), 5);
    scene.addItem(&paddle);

    Ball ball(QRect(0, 0, 10, 10), 5);
    scene.addItem(&ball);

    GameView view(&scene);

    GameManager gameManager(&view, screenSize.height(), screenSize.width());
    gameManager.addEntity(&paddle);
    gameManager.addEntity(&ball);
    gameManager.addEntity(&gameManager);
    gameManager.start();

    view.setFixedSize(screenSize);
    view.show();

    return a.exec();
}
