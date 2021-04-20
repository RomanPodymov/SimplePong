//
//  gameentity.cpp
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#import "gameentity.h"

GameEntity::GameEntity(QRect entityRect, int stepSize): entityRect(entityRect),
    stepSize(stepSize) {

}

void GameEntity::setupInitialState(GameManager* gameManager, bool) {
    entityRect = initialEntityRect(gameManager);
    drawEntity();
}

void GameEntity::onGameReset(GameManager* gameManager) {
    setupInitialState(gameManager, false);
}

QRect GameEntity::nextEntityRect(int dx, int dy) const {
    return QRect(
        entityRect.x() + dx,
        entityRect.y() + dy,
        entityRect.size().width(),
        entityRect.size().height()
    );
}
