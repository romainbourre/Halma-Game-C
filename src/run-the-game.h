//
//  run-the-game.h
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include <stdio.h>

#include "structures.h"



void new_game(globalSettings init);

void search_load();

void start_game(gameSettings play, int * plateau);

int sub_menu(int * plateau, gameSettings play);


