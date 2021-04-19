//
//  gameview.h
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class GameView final: public QGraphicsView {
    Q_OBJECT

public:
    GameView(QGraphicsScene* scene, QWidget *parent = nullptr);

signals:
    void mouseMoveLeft();
    void mouseMoveRight();

protected:
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPointF previousMouseLocalPos;
};

#endif // GAMEVIEW_H
