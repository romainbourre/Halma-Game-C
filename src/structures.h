//
//  structures.h
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#ifndef structures_h
#define structures_h

// STRUCTURES DE DEPLACEMENTS //

/**
 structure incluant des coordonnées x et y
 */
typedef struct coord {
    
    int y;
    int x;
    
    
} coord;



/**
 Structure incluant les coordonnées x et y d'une source et d'une destination
 */
typedef struct coordMov {
    
    coord src;
    coord dest;
    
} coordMov;



/**
 Structure contenant les paramètres globaux du jeu
 */
typedef struct globalSettings {
    
    int taillePlateauY;
    int taillePlateauX;
    int nbrPions_12;
    int nbrPions_34;
    
} globalSettings;



/**
 Structure contenant les paramètres de la partie
 */
typedef struct gameSettings {
    
    // Paramètre de la partie en cours //
    int nbrPlayers;
    int roundPlayer;
    int pos1PlayerWin;
    int pos2PlayerWin;
    int pos3PlayerWin;
    int pos4PlayerWin;
    int nbrPions;
    coordMov movePawn;
    
    // Paramètres globaux //
    int taillePlateauY;
    int taillePlateauX;
    int nbrPions_12;
    int nbrPions_34;
    
} gameSettings;

#endif /* structures_h */
