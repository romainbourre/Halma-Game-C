//
//  init-the-game.h
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include <stdio.h>

#include "structures.h"


void init_board(int * plateau, gameSettings play);

int set_game(int * plateau, struct gameSettings * play);

void init_pawns(int * plateau, gameSettings * play, int numJoueur, int positionPlayer);

