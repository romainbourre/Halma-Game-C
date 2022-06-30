//
//  move_pawn.c
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include "structures.h"

#include "move-the-pawn.h"
#include "in-out-shell.h"
#include "general-function.h"




/**
 Détecte si une case du plateau est vide

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @param Y ordonnée de la case à vérifier
 @param X abscisse de la case à vérifier
 @return 1 si la case est vide
 @return 0 si la case est non vide
 */
int check_pawnNULL(int plateau[], gameSettings play, int Y, int X) {
    
    int pawn_statut = 0;
    
    if (plateau[Y*play.taillePlateauX+X] == 0) {
        
        pawn_statut = 1;
        
    }
    else {
        
        pawn_statut = 0;
        
    }
    
    return pawn_statut;
    
}




/**
 Compte le nombre de saut possible

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @param Y ordonnée de la case intermédiaire enter la source et la destination
 @param X abscisse de la case intermédiaire enter la source et la destination
 @return le nombre de saut possible
 */
int multi_jump(int * plateau, gameSettings play, int Y, int X) {
    
    int checkAroundY = play.movePawn.dest.y - 1;
    int checkAroundX = play.movePawn.dest.x - 1;
    
    int nextPawnY;
    int nextPawnX;
    
    int movePossible = 0;
    
    for(int i = checkAroundY; i < (checkAroundY + 3); i++) {
        
        for(int j = checkAroundX; j < (checkAroundX + 3); j++) {
            
            if((i != play.movePawn.src.y || j != play.movePawn.src.x) || (i != Y || j != X)) {
                
                if(plateau[i*play.taillePlateauX+j]) {
                    
                    nextPawnY = i + ( i - play.movePawn.dest.y );
                    nextPawnX = j + ( j - play.movePawn.dest.x );
                    
                    if( ( nextPawnY >= 0 && nextPawnY <= (play.taillePlateauY-1) ) && ( nextPawnX >= 0 && nextPawnX <= (play.taillePlateauX-1) ) ) {
                    
                        if(check_pawnNULL(plateau, play, nextPawnY, nextPawnX)) {
                        
                            movePossible++;
                        
                        }
                        else {
                        
                     
                        
                        }
                    }
                    
                }
                
            }
            
        }
        
    }
    
    return movePossible;

}

/**
 Vérifie la validité du mouvement et détermine son type

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @return 0 si le mouvement n'est pas valide
 @return 1 si le mouvement est simple
 @return 100 + le nombre de mouvement encore possible si c'est un saut
 */
int check_move(int * plateau, gameSettings play) {
    
    int jump_statut = 0;
    
    // Détermine la distance entre deux cases.
    int differentY = play.movePawn.dest.y - play.movePawn.src.y;
    int differentX = play.movePawn.dest.x - play.movePawn.src.x;
    
    int pawnJumpY = 0;
    int pawnJumpX = 0;
    
    if(check_pawnNULL(plateau, play, play.movePawn.dest.y, play.movePawn.dest.x)) {
        // La case de destination n'est pas vide
        
        if( (differentY == 2 || differentY == -2) || (differentX == 2 || differentX == -2) ) {
            // Le mouvement est un saut
            
            // Détermine les coordonnées de la case intermédiaire
            pawnJumpY = play.movePawn.src.y + ((play.movePawn.dest.y - play.movePawn.src.y)/2);
            pawnJumpX = play.movePawn.src.x + ((play.movePawn.dest.x - play.movePawn.src.x)/2);
            
            if(!check_pawnNULL(plateau, play, pawnJumpY, pawnJumpX)) {
                // La case intermédiaire n'est pas vide
                
                // Véifie si d'autres sauts sont encore possibles
                jump_statut = 100 + multi_jump(plateau, play, pawnJumpY, pawnJumpX);
                
            }
                
        }
        else if( (differentY == 1 || differentY == -1) || (differentX == 1 || differentX == -1) ) {
            // Le mouvement est simple
            
                jump_statut = 1;
                
        }
        else {
                
            jump_statut = 0;
                
        }
       
    }
    else {
        
        jump_statut = 0;
        
    }
    
    return jump_statut;
    
}



/**
 Déplace le pion d'une case vers une autre

 @param plateau plateau du jeu
 @param play paramèters du jeu
 @param previousCheckMove la valeur du mouvement précédent
 @return 0 si le mouvement n'est pas valide
 @return 1 si le mouvement est simple
 @return 2 si la case de destination est la même que la source, pas d'action, joueur suivant
 @return 100 + le nombre de saut encore possible en cas de saut
 @return -1 si la case de départ ou de destination sort du plateau
 @return -2 si la case de départ n'appartient pas au joueur
 @return -3 si le joueur enchaîne un mouvement simple après un saut
 */
int move_pawn(int * plateau, gameSettings play, int previousCheckMove) {
    
    int move_statut = 0;
    
    if( ( play.movePawn.src.y >= 0 && play.movePawn.src.y <= (play.taillePlateauY-1) ) && ( play.movePawn.src.x >= 0 && play.movePawn.src.x <= (play.taillePlateauX-1) ) && ( play.movePawn.dest.y >= 0 && play.movePawn.dest.y <= (play.taillePlateauY-1) ) && ( play.movePawn.dest.x >= 0 && play.movePawn.dest.x <= (play.taillePlateauX-1) ) ) {
        
        if(play.movePawn.dest.y != play.movePawn.src.y || play.movePawn.dest.x != play.movePawn.src.x) {

            if(!check_pawnNULL(plateau, play, play.movePawn.src.y, play.movePawn.src.x)) {
            
                if(plateau[play.movePawn.src.y*play.taillePlateauX+play.movePawn.src.x] == play.roundPlayer) {
            
                    move_statut = check_move(plateau, play);
        
                    if(move_statut == 1) {
                        // Le joueur effectue un mouvement simple
        
                        if(previousCheckMove == 0) {
                            // Vérifie que le joueur n'a pas déjà effectué un saut.
                            
                            plateau[play.movePawn.dest.y*play.taillePlateauX+play.movePawn.dest.x] = plateau[play.movePawn.src.y*play.taillePlateauX+play.movePawn.src.x];
                            plateau[play.movePawn.src.y*play.taillePlateauX+play.movePawn.src.x] = 0;
                
                        }
                        else {
                            
                            printf("\nCe mouvement est interdit après un saut\n");
                            move_statut = -3;
                            
                        }
                            
                    }
                    else if(move_statut >= 100) {
                        // Le joueur effectue un saut
                    
                        plateau[play.movePawn.dest.y*play.taillePlateauX+play.movePawn.dest.x] = plateau[play.movePawn.src.y*play.taillePlateauX+play.movePawn.src.x];
                        plateau[play.movePawn.src.y*play.taillePlateauX+play.movePawn.src.x] = 0;
                    
                        if(move_statut > 100) {
                            // Il reste des mouvements possibles au joueur
                        
                            play.movePawn.src.y = play.movePawn.dest.y;
                            play.movePawn.src.x = play.movePawn.dest.x;
                    
                            do {
                    
                                display_title("HALMA", play.taillePlateauX);
                    
                                display_board((int *)plateau, play);
                    
                                printf("Tu as encore des possibilités Joueur %d !\n", play.roundPlayer);
                            
                                get_coord((int *)plateau, &play, 0);
                    
                                move_statut = move_pawn(plateau, play, move_statut);
                        
                            } while (move_statut < 0);
                            
                        }
                    
                    }
        
                }
                else {
                
                    move_statut = -2;
                
                }
                
            }
            
        }
        else {
        
            move_statut = 2;
            
        }
        
    }
    else {
            
        move_statut = -1;
            
    }
    
    return move_statut;
    
}
