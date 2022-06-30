//
//  in-out-shell.h
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include <stdio.h>

#include "structures.h"



void display_board(int *plateau, gameSettings play);

void display_title(char text[], int taillePlateauX);

int get_coord(int * plateau, gameSettings * play, int onX);

int get_string(char * chaine, int longueur);

void clear_console();

void print_color(char text[], char colorFont[], char colorBack[]);

void define_font(char colorFont[]);

void define_back(char colorBack[]);

