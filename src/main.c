//
//  main.c
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include <stdio.h>

#include "structures.h"

#include "in-out-shell.h"
#include "run-the-game.h"
#include "general-function.h"

#define COLOR_ACTIVE 0

int main(int argc, const char * argv[]) {
    
    int colorActive = COLOR_ACTIVE;
    
    // Initialisation des paramètres globaux
    globalSettings init;
    init.nbrPions_12 = 15;
    init.nbrPions_34 = 6;
    init.taillePlateauY = 10;
    init.taillePlateauX = 10;
    
    int menuChoice = 0;
    
    do {
    
        display_title("HALMA", init.taillePlateauX);
    
        printf("Que voulez vous faire ?\n\n");
    
        printf("1. Nouvelle partie\n");
        printf("2. Charger une partie\n");
        //printf("3. Paramètres (indisponible)\n");
        printf("0. Quitter\n\n");
    
        if(colorActive == 1) {
            print_color("Choix : ", "yellow", "black");
        }
        else {
            printf("Choix : ");
        }
        scanf("%1d", &menuChoice);
        empty_buffer();
    
        switch (menuChoice) {
            
            case 1:
                // lancement d'une nouvelle partie
                new_game(init);
                break;
                
            case 2:
                // Chargement d'une partie enregistrée
                search_load();
                break;
                
            default:
                break;
            
        }
        
    } while (menuChoice != 0);
    
    display_title("HALMA", init.taillePlateauX);
    printf("À bientôt !\n\n");
    sleep_prog(3);
    clear_console();
    
}
