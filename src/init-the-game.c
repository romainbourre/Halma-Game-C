//
//  init-the-game.c
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include "structures.h"

#include "init-the-game.h"
#include "general-function.h"
#include "run-the-game.h"



/**
 Met en place les pions sur la plateau

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @param numJoueur numéro du joueur
 @param positionPlayer position du joueur
 */
void init_pawns(int * plateau, gameSettings * play, int numJoueur, int positionPlayer) {
    
    int posPlayerWin;
    int triangleCompose;
    
    triangleCompose = int_compose(play->nbrPions);
    
    // Composition de la zone du joueur
    switch (positionPlayer) {
        
        case 1: // en bas à droite
            
            for(int y = 0 ; y < triangleCompose; y++) {
                
                for(int x = (play->taillePlateauX-1); x > ((play->taillePlateauX-1) - (triangleCompose-y)); x--) {
                    
                    plateau[y*play->taillePlateauX+x] = numJoueur;
                    
                }
                
            }
            
        break;
         
        case 2: // en bas à gauche
            for(int y = 0 ; y < triangleCompose; y++) {
                
                for(int x = 0; x <= (triangleCompose-1-y); x++) {
                    
                    plateau[y*play->taillePlateauX+x] = numJoueur;
                    
                }
                
            }
        break;
            
        case 3: // en haut à gauche
            for(int y = (play->taillePlateauY-1) ; y >= triangleCompose; y--) {
                
                for(int x = 0; x < (((play->taillePlateauX-1) - ((play->taillePlateauX-1)-triangleCompose))-((play->taillePlateauY-1)-y)); x++) {
                    
                    plateau[y*play->taillePlateauX+x] = numJoueur;
                    
                }
                
            }
        break;
        
        case 4: // en haut à droite
            for(int y = (play->taillePlateauY-1); y >= triangleCompose; y--) {
                
                for(int x = (play->taillePlateauX-1); x > ((play->taillePlateauX-1) - triangleCompose)+((play->taillePlateauY-1)-y); x--) {
                    
                    plateau[y*play->taillePlateauX+x] = numJoueur;
                    
                }
                
            }
        break;
    
    }
    
    
    // Determine le joueur gagnant par position
    posPlayerWin = positionPlayer + 2;
    if(posPlayerWin > 4) {
        
        posPlayerWin -= 4;
        
    }
    
    switch (posPlayerWin) {
            
        case 1:
            play->pos1PlayerWin = numJoueur;
            break;
            
        case 2:
            play->pos2PlayerWin = numJoueur;
            break;
        case 3:
            play->pos3PlayerWin = numJoueur;
            break;
        case 4:
            play->pos4PlayerWin = numJoueur;
            break;
            
        default:
            break;
            
    }
        
}


/**
 Initialise le plateau du jeu à zéro

 @param plateau plateau du jeu
 @param play paramètres de la partie
 */
void init_board(int * plateau, gameSettings play) {

    
    for(int i = 0; i < play.taillePlateauY; i++) {
        
        for(int j = 0; j < play.taillePlateauX; j++) {
            
            plateau[i*play.taillePlateauX+j] = 0;
            
        }
        
    }
    
}



/**
 Met en place le plateau du jeu

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @return  0 quand l'installation s'est bien déroulée
 @return -1 quand l'installation des pions a échouée
 */
int set_game(int * plateau, struct gameSettings* play) {
    
    play->nbrPions = 0;
    int set_statut;
    
    play->pos1PlayerWin = 0;
    play->pos2PlayerWin = 0;
    play->pos3PlayerWin = 0;
    play->pos4PlayerWin = 0;
    
    // Mise à zéro du plateau
    init_board(plateau, *play);
    
    // Détermine le nombre de pion à installer par joueur
    if(play->nbrPlayers == 1 || play->nbrPlayers == 2) {
        
        play->nbrPions = play->nbrPions_12;
        
    }
    else if(play->nbrPlayers == 3 || play->nbrPlayers == 4) {
        
        play->nbrPions = play->nbrPions_34;
        
    }
    
    // Installation des pions sur la plateau
    if(play->nbrPlayers == 2) {
        
        init_pawns(plateau, play, 1, 1);
        init_pawns(plateau, play, 2, 3);
        
        set_statut = 0;
        
    }
    else if( ( play->nbrPlayers > 2 && play->nbrPlayers <= 4 ) || play->nbrPlayers == 1 ) {
        
        for(int n = 1; n <= play->nbrPlayers; n++) {
            
            init_pawns(plateau, play, n, n);
            
        }
        
        set_statut = 0;
        
    }
    else {
        
        set_statut = -1;
        
    }
    
    return set_statut;
    
}
