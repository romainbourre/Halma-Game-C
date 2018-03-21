//
//  check-the-game.c
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include "structures.h"

#include "check-the-game.h"
#include "in-out-shell.h"
#include "general-function.h"



/**
 Recherche le joueur gagnant de la partie

 @param plateau plateau du jeu
 @param play paramètres du jeu
 @return 0 si pas de gagnant
 @return le joueur gagnant
 */
int check_winner(int * plateau, gameSettings play) {
    
    int playerZone1 = -1;
    int playerZone2 = -1;
    int playerZone3 = -1;
    int playerZone4 = -1;
    
    int playerWin = 0;
    
    int triangleCompose = int_compose(play.nbrPions);
    
    
    // Analyse de la zone en bas à droite (1) //
    if(play.pos1PlayerWin != 0) {
    
        playerZone1 = plateau[play.taillePlateauX-1];
    
        for(int y = 0 ; y < triangleCompose; y++) {
        
            for(int x = (play.taillePlateauX-2); x > ((play.taillePlateauX-1) - (triangleCompose-y)); x--) {
            
                if(plateau[y*play.taillePlateauX+x] == 0 || plateau[y*play.taillePlateauX+x] != playerZone1) {
                
                    playerZone1 = -1;
                
                }
            
            }
        
        }
        
    }
    
    
    // Analyse de la zone en bas à gauche (2) //
    if(play.pos2PlayerWin != 0) {
    
        playerZone2 = plateau[0];
    
        for(int y = 0 ; y < triangleCompose; y++) {
        
            for(int x = 1; x <= (triangleCompose-1-y); x++) {
            
                if(plateau[y*play.taillePlateauX+x] == 0 || plateau[y*play.taillePlateauX+x] != playerZone2) {
                
                    playerZone2 = -1;
                
                }
            
            }
        }
        
    }
    
    
    // Analyse de la zone en haut à gauche (3) //
    if(play.pos3PlayerWin != 0) {
    
        playerZone3 = plateau[(play.taillePlateauY-1)*play.taillePlateauX+1];
    
        for(int y = (play.taillePlateauY-1) ; y >= triangleCompose; y--) {
        
            for(int x = 0; x < (((play.taillePlateauX-1) - ((play.taillePlateauX-1)-triangleCompose))-((play.taillePlateauY-1)-y)); x++) {
            
                if(plateau[y*play.taillePlateauX+x] == 0 || plateau[y*play.taillePlateauX+x] != playerZone3) {
                
                    playerZone3 = -1;
                
                }
            
            }
        }
        
    }
    
    
    // Analyse de la zone en haut à droite (4) //
    if(play.pos4PlayerWin != 0) {
    
        playerZone4 = plateau[play.taillePlateauY*play.taillePlateauX];
    
        for(int y = (play.taillePlateauY-1); y >= triangleCompose; y--) {
        
            for(int x = (play.taillePlateauX-2); x > ((play.taillePlateauX-1) - triangleCompose)+((play.taillePlateauY-1)-y); x--) {
            
                if(plateau[y*play.taillePlateauX+x] == 0 || plateau[y*play.taillePlateauX+x] != playerZone4) {
                
                    playerZone4 = -1;
                
                }
            
            }
        
        }
        
    }
    
    if(playerZone1 == play.pos1PlayerWin) {
        playerWin = playerZone1;
    }
    else if(playerZone2 == play.pos2PlayerWin) {
        playerWin = playerZone2;
    }
    else if(playerZone3 == play.pos3PlayerWin) {
        playerWin = playerZone3;
    }
    else if(playerZone4 == play.pos4PlayerWin) {
        playerWin = playerZone4;
    }
    
    return playerWin;
    
}



/**
 Vérifie le déroulement de la partie

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @return 100 + le numéro du joueur gagnant
 */
int check_game(int * plateau, gameSettings play) {
//-------------------------------------------------------------------------------------------------------//
// [Action] Vérifie le jeu.                                                                              //
//-------------------------------------------------------------------------------------------------------//
    
    int checkGame_statut = 0;
    int resultWinner = 100;
    
   
    // Analyse le jeu pour savoir s'il y a un gagnant //
    resultWinner += check_winner((int *)plateau, play);
    
    checkGame_statut = resultWinner;
    
    return checkGame_statut;
    
}


