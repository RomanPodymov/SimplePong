//
//  gameview.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#include "gameview.h"

GameView::GameView(QGraphicsScene* scene, QWidget *parent): QGraphicsView(scene, parent) {

}

void GameView::mouseMoveEvent(QMouseEvent *event) {
    const auto& nextMouseLocalPos = event->position();
    if (nextMouseLocalPos.x() < previousMouseLocalPos.x()) {
        emit mouseMoveLeft();
    } else if (nextMouseLocalPos.x() > previousMouseLocalPos.x()) {
        emit mouseMoveRight();
    }
    previousMouseLocalPos = nextMouseLocalPos;
}
