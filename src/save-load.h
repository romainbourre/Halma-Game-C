//
//  save-load.h
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include <stdio.h>

#include "structures.h"




int save_game(int * plateau, gameSettings play);

int load_game(int numLoad, int ** plateau, gameSettings * play);

int display_load(int displayOnOff);
