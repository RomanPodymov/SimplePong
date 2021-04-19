//
//  gamefield.h
//  App
//
//  Created by Roman Podymov on 19/04/2021.
//  Copyright © 2021 SimplePong. All rights reserved.
//

#ifndef GAMEFIELD_H
#define GAMEFIELD_H

class GameField {

public:
    GameField(int gameFieldRows, int gameFieldColumns);

public:
    const int gameFieldRows;
    const int gameFieldColumns;
};

#endif // GAMEFIELD_H
