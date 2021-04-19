//
//  gamefield.h
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "gameentity.h"

class GameField: public GameEntity {

public:
    GameField(int gameFieldRows, int gameFieldColumns);
    int gameFieldColumns() const { return entityRect.width(); }
    int gameFieldRows() const { return entityRect.height(); }
};

#endif // GAMEFIELD_H
