//
//  run-the-game.c
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include <stdlib.h>
#include <time.h>

#include "structures.h"

#include "in-out-shell.h"
#include "init-the-game.h"
#include "move-the-pawn.h"
#include "check-the-game.h"
#include "run-the-game.h"
#include "save-load.h"
#include "general-function.h"



/**
 Affiche le sous-menu en cours de partie

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @return -1 si le jeu a été sauvegardé
 @return -2 si le joueur quitte la partie
 */
int sub_menu(int * plateau, gameSettings play) {
    
    int subMenu_statut = 0;
    int choiceMenu;
    
    display_title("PAUSE", 0);
    printf("1. Enregistrer la partie\n");
    printf("2. Reprendre la partie\n");
    printf("0. Quitter la partie\n");
    
    printf("\nQue voulez-vous faire ? ");
    scanf("%d", &choiceMenu);
    
    switch (choiceMenu) {
        case 0:
            subMenu_statut = -2;
            break;
            
        case 1:
            save_game((int *)plateau, play);
            subMenu_statut = -1;
            break;
        
        case 2:
            subMenu_statut = -1;
            break;
        
        default:
            break;
    }
    
    return subMenu_statut;
    
}

/**
 Initialise une nouvelle partie

 @param init paramètres globaux du jeu
 */
void new_game(globalSettings init) {
    
    // Création des paramètres de la partie //
    gameSettings play;
    
    // Implémentation des paramètres globaux dans les paramètres de la partie //
    play.nbrPions_12 = init.nbrPions_12;
    play.nbrPions_34 = init.nbrPions_34;
    play.taillePlateauY = init.taillePlateauY;
    play.taillePlateauX = init.taillePlateauX;
    
    // Initialisation des paramètres de la partie
    play.roundPlayer = 1;
    
    // Création du plateau de jeu
    int plateau[play.taillePlateauY][play.taillePlateauX];
    
    do {
        
        display_title("NOUVELLE PARTIE", play.taillePlateauX);
    
        printf("Combien de joueur\n êtes vous (2 à 4 joueurs) ? ");
        scanf("%1d", &play.nbrPlayers);
        empty_buffer();
        
    } while(play.nbrPlayers <= 1 || play.nbrPlayers > 4);
    
    // initialisation de la partie
    set_game((int *)plateau, &play);
    
    // lancement du jeu
    start_game(play, (int *)plateau);
    
}




/**
 Recherche, affiche les parties enregistrées et charge la partie choisi
 */
void search_load() {

    gameSettings play;
    int * plateau = NULL;
    int nbrGame = 0;
    int numGame = 0;
    
    display_title("CHARGER UNE PARTIE", 0);
    printf("0. Retour au menu\n\n");
    
    nbrGame = display_load(1);
    
    if(nbrGame > 0) {
    
        printf("Quelle partie voulez-vous charger ? ");
        scanf("%d", &numGame);
        
        if(numGame > 0) {
    
            load_game(numGame, &plateau, &play);
    
            start_game(play, (int *)plateau);
        
            free(plateau);
            
        }
   
    }
    else {
        
        display_title("CHARGER UNE PARTIE", 0);
        printf("Aucune partie de disponible.\n\n");
        sleep_prog(3);
        
    }
    
}


/**
 Lancement de la partie

 @param play paramètres de la partie
 @param plateau plateau du jeu
 */
void start_game(gameSettings play, int * plateau) {
    
    int gameStatut = 0;
    int round_statut = 0;
    int playerWin = 0;
    
    
    do {
        
        
        
        if(play.roundPlayer > play.nbrPlayers) {
            
            play.roundPlayer = 1;
            
        }
        
        
        
        do {
            
            gameStatut = 0;
            
            display_title("HALMA", play.taillePlateauX);
            
            printf("0. Mettre le jeu en pause\n\n");
            
            if(round_statut == -1) {
                
                print_color("\nFais attention à selectionner une\n case du plateau...\n", "red", "black");
                
            }
            else if(round_statut == -2) {
                
                print_color("\nTu ferais mieux de toucher à tes pions...\n", "red", "black");
                
            }
            
            display_board((int *)plateau, play);
            
            printf("\nAllez Joueur %d, c'est à toi de jouer.\n", play.roundPlayer);
            
            gameStatut = get_coord((int *)plateau, &play, 1);
            
            if(gameStatut >= 0) {
                round_statut = move_pawn((int *)plateau, play, 0);
            }
        
            
        } while (round_statut < 0 || gameStatut == -1);
        
        
        if(gameStatut == 0) {
            play.roundPlayer++;
            playerWin = check_game((int *)plateau, play);
        }
        
    } while (playerWin <= 100 && gameStatut != -2);
    
    if(playerWin > 100) {
        
        display_title("PARTIE TERMINÉ !", play.taillePlateauX);
        printf("\n\nLe joueur %d gagne !\n\n", playerWin-100);
        sleep_prog(3);
        
    }
    
}
