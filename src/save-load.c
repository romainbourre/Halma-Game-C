//
//  save-load.c
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"

#include "save-load.h"
#include "run-the-game.h"
#include "in-out-shell.h"
#include "general-function.h"

#define SIZE_NAME_GAME 25



/**
 Enregistre la partie en cours

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @return  0 si l'enregistrement s'est bien déroulé
 @return -1 en cas de problème lors de l'ouverture du fichier
 */
int save_game(int * plateau, gameSettings play) {
    
    int save_statut = 0;
    FILE* backup = NULL;
    char nameGame[SIZE_NAME_GAME];
    int nbrLoad = display_load(0);
    int numGame;
    
    // Définie le numéro d'enregistrement
    if(nbrLoad == -1) {
        
        numGame = 1;
        
    }
    else {
        
        numGame = nbrLoad + 1;
        
    }
    
    backup = fopen("backup.halma", "a");
    
    if(backup != NULL) {
        
        display_title("ENREGISTRER", 0);
        printf("Nom de la partie : ");
        get_string(nameGame, SIZE_NAME_GAME);
        
        fprintf(backup, "%d: | %s | (%d %d %d %d) (%d %d %d %d %d %d %d) ", numGame, nameGame, play.taillePlateauX,play.taillePlateauY, play.nbrPions_12, play.nbrPions_34, play.nbrPlayers, play.nbrPions, play.pos1PlayerWin, play.pos2PlayerWin, play.pos3PlayerWin, play.pos4PlayerWin, play.roundPlayer);
        
        fprintf(backup, "[ ");
        for(int y = 0; y < play.taillePlateauY; y++) {
            
            for(int x = 0; x < play.taillePlateauX; x++) {
                
                fprintf(backup, "%d ", plateau[y*play.taillePlateauX+x]);
                
            }
            
        }
        fprintf(backup, "]\n");
        
        fclose(backup);
        
    }
    else {
        
        save_statut = -1;
        
    }
    
    return save_statut;
    
}

/**
 Retourne le nombre de partie enregistré et les affiche (si demandé)

 @param displayOnOff si 1 alors les parties enregistrées seront affichées
 @return nombre de partie disponible
 @return -1 si problème à l'ouveture du fichier
 */
int display_load(int displayOnOff) {
    
    int numGame = 0;
    int nbrGame = 0;
    char nameGame[SIZE_NAME_GAME] = {'\0'};
    char readCaract;
    int i = -1;
    int readCar = 0;
    
    FILE* backup = NULL;
    
    backup = fopen("backup.halma", "r");
    
    if(backup != NULL) {
        
        if(displayOnOff == 1) {
            
            display_title("CHARGER UNE PARTIE", 0);
            printf("0. Retour au menu\n\n");
            
        }
        
        do {
            
                fscanf(backup, "%d: | ", &numGame);
            
                if(numGame != 0) {
                    nbrGame++;
                }
            
                if(displayOnOff == 1) {
            
                    // Lecture du nom de la partie
                    do {
                
                        i++;
                        readCaract = fgetc(backup);
                        if (readCaract != '|') {
                            nameGame[i] = readCaract;
                        }
                        else {
                            i =SIZE_NAME_GAME;
                        }
                    
                    } while (nameGame[i] != '|' && i < 25);
            
            
                    // Affichage de la partie disponible
                    if(numGame > 0) {
                        
                        printf("%d. %s\n", numGame, nameGame);
                    }
            
                    i = -1;
                    init_string((char *)nameGame, SIZE_NAME_GAME);
        
                }
            
        
            do {
                // Va à la ligne suivante
                readCar = getc(backup);
            } while(readCar != '\n' && readCar != EOF);
            
            numGame = 0;
            
        } while (readCar != EOF);
        printf("\n");
        
        fclose(backup);
        
    }
    else {
        
        nbrGame = -1;
        
    }
    
    return nbrGame;
    
}

/**
 Initialise la partie à partir d'une sauvegarde

 @param numLoad numéro de la partie à charger
 @param plateau plateau du jeu
 @param play paramètres de la partie
 @return  0 si le chargement est effectué
 @return -1 si problème lors de l'ouverture du fichier
 */
int load_game (int numLoad, int ** plateau, gameSettings * play) {
//------------------------------------------------------------------------------------------------------//
// [Action] Initialise la partie à partir d'une partie sauvegardée.                                     //
//                                                                                                      //
// [Retourne]   0 la partie est chargé.                                                                 //
//             -1 si problème à l'ouverture du fichier de sauvegarde.                                   //
//------------------------------------------------------------------------------------------------------//
    
    int load_statut = 0;
    
    int numGame;
    int * plateau2 = NULL;
    
    char nameGame[SIZE_NAME_GAME] = {'\0'};
    char readCaract;
    int i = -1;
    
    int readCar = 0;
    
    FILE* backup = NULL;
    
    backup = fopen("backup.halma", "r");
    
    if(backup != NULL) {
        
        do {
            
            fscanf(backup, "%d: | ", &numGame);
        
            if(numGame == numLoad) {
        
                // Lecture du nom de la partie
                do {
                    
                    i++;
                    readCaract = fgetc(backup);
                    if (readCaract != '|') {
                        nameGame[i] = readCaract;
                    }
                    else {
                        i =SIZE_NAME_GAME;
                    }
                    
                } while (nameGame[i] != '|' && i < SIZE_NAME_GAME);
                
                // Chargement des paramètres de la partie
                fscanf(backup, " (%d %d %d %d) (%d %d %d %d %d %d %d) [ ", &play->taillePlateauX, &play->taillePlateauY, &play->nbrPions_12, &play->nbrPions_34, &play->nbrPlayers, &play->nbrPions, &play->pos1PlayerWin, &play->pos2PlayerWin, &play->pos3PlayerWin, &play->pos4PlayerWin, &play->roundPlayer);
        
        
                // Chargement du plateau sauvegardé
                plateau2 = malloc((play->taillePlateauY*play->taillePlateauX)*sizeof(int));
        
                for(int y = 0; y < play->taillePlateauY; y++) {
            
                    for(int x = 0; x < play->taillePlateauX; x++) {
        
                        fscanf(backup, "%d ", &plateau2[y*play->taillePlateauX+x]);
                
                    }
            
                }
                
                *plateau = plateau2;
                
                readCar = EOF;
            
            }
            else {
                
                // Ligne suivante
                do {
                    readCar = getc(backup);
                } while(readCar != '\n' && readCar != EOF);
                
                
            }
            
            numGame = 0;
            i = -1;
            init_string((char *)nameGame, SIZE_NAME_GAME);
            
        } while (readCar != EOF);
        
        fclose(backup);
        
    }
    else {
        
        load_statut = -1;
        
    }
    
    return load_statut;
    
}
