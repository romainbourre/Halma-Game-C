//
//  in-out-shell.c
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//

#include <string.h>

#include "structures.h"

#include "run-the-game.h"
#include "in-out-shell.h"
#include "general-function.h"

#define COLOR_ACTIVE 0

/**
 Efface la console
 */
void clear_console() {
    
    printf("\033[H\033[2J");
    
}

/**
 Définition d'une couleur pour le texte

 @param colorFont couleur demandée
 */
void define_font(char colorFont[]) {
    
    int colorCodeFont = 0;
    
    if(!strcmp(colorFont, "black")) {
        colorCodeFont = 30;
    }
    else if(!strcmp(colorFont, "red")) {
        colorCodeFont = 31;
    }
    else if(!strcmp(colorFont, "green")) {
        colorCodeFont = 32;
    }
    else if(!strcmp(colorFont, "yellow")) {
        colorCodeFont = 33;
    }
    else if(!strcmp(colorFont, "blue")) {
        colorCodeFont = 34;
    }
    else if(!strcmp(colorFont, "magenta")) {
        colorCodeFont = 35;
    }
    else if(!strcmp(colorFont, "cyan")) {
        colorCodeFont = 36;
    }
    else if(!strcmp(colorFont, "white")) {
        colorCodeFont = 37;
    }
    else {
        colorCodeFont = 0;
    }

    printf("\033[%dm", colorCodeFont);
    
}

/**
 Définition d'une couleur pour le fond

 @param colorBack couleur demandée
 */
void define_back(char colorBack[]) {
    
    int colorCodeBack = 0;
    
    if(!strcmp(colorBack, "black")) {
        colorCodeBack = 40;
    }
    else if(!strcmp(colorBack, "red")) {
        colorCodeBack = 41;
    }
    else if(!strcmp(colorBack, "green")) {
        colorCodeBack = 42;
    }
    else if(!strcmp(colorBack, "yellow")) {
        colorCodeBack = 43;
    }
    else if(!strcmp(colorBack, "blue")) {
        colorCodeBack = 44;
    }
    else if(!strcmp(colorBack, "magenta")) {
        colorCodeBack = 45;
    }
    else if(!strcmp(colorBack, "cyan")) {
        colorCodeBack = 46;
    }
    else if(!strcmp(colorBack, "white")) {
        colorCodeBack = 47;
    }
    else {
        colorCodeBack = 0;
    }

    printf("\033[%dm", colorCodeBack);
    
}

/**
 Affiche du texte en couleur dans la console

 @param text texte à afficher
 @param colorFont couleur du texte
 @param colorBack couleur du fond
 */
void print_color(char text[], char colorFont[], char colorBack[]) {
    
    define_font(colorFont);
    define_back(colorBack);
    printf("%s", text);
    printf("\033[0m");
    
}

/**
 Affiche en mode console le plateau du jeu

 @param plateau plateau du jeu
 @param play paramètres de la partie
 */
void display_board(int *plateau, gameSettings play) {
    
    int colorActive = COLOR_ACTIVE;
    
    int taillePlateauY = play.taillePlateauY;
    int taillePlateauX = play.taillePlateauX;
    
    int ligneY;
    int pions = 0;
    
    printf("\n");
    
    for(int y = (taillePlateauY-1); y >= 0; y--) {
        
        ligneY = y + 1;
        
        // Création de la ligne supérieur //
        printf("   ");
        for(int traceX = 0; traceX < taillePlateauX; traceX++){
            
            if(colorActive == 1) {
                print_color("----", "black", "white");
            }
            else {
                printf("----");
            }
            
        }
        if(colorActive == 1) {
            print_color("-", "black", "white");
        }
        else {
            printf("-");
        }
        
        // Numérotation Ordonnée //
        if(ligneY < 10) {
            
            printf("\nO%d ", ligneY);
        }
        else {
            printf("\n%d ", ligneY);
        }
        
        // Affichage des données par ligne //
        for(int x = 0; x < taillePlateauX; x++ ) {
            
            pions = plateau[y*taillePlateauX+x];
            
            if(pions != 0) {
                
                if(colorActive == 1) {
                    define_font("black");
                    define_back("white");
                    printf("| %d ", pions);
                    define_font("");
                    define_back("");
                }
                else {
                    printf("| %d ", pions);
                }
                
            }
            else {
                
                if(colorActive == 1) {
                    print_color("|   ", "black", "white");
                }
                else {
                    printf("|   ");
                }
                
            }
            
        }
        
        if(colorActive == 1) {
            print_color("|\n", "black", "white");
        }
        else {
            printf("|\n");
        }
        
    }
    
    
    // Tracé de la ligne inférieur //
    printf("   ");
    for(int traceX = 0; traceX < taillePlateauX; traceX++){
        
        if(colorActive == 1) {
            print_color("----", "black", "white");
        }
        else {
            printf("----");
        }
        
    }
    if(colorActive == 1) {
        print_color("-\n", "black", "white");
    }
    else {
        printf("-\n");
    }
    printf("    ");
    
    // Numérotation Abscisse //
    for(int x = 1; x <= taillePlateauX; x++ ) {
        
        if(x < 10) {
            printf(" 0%d ", x);
        }
        else {
            printf(" %d ", x);
        }
    }
    
    printf("\n\n");
    
}


/**
 Affiche un titre principal.

 @param text texte à afficher
 @param taillePlateauX largeur du titre
 */
void display_title(char text[], int taillePlateauX) {
    
    int cpt = 0;
    int cptRest = 0;
    long tailleText = strlen(text);
    
    if(taillePlateauX < 10) {
        
        taillePlateauX = 10;
        
    }
    
    clear_console();
    
    // Ligne 1 //
    printf("***");
    for(int traceX = 0; traceX < taillePlateauX; traceX++){
        
        printf("****");
        
    }
    printf("*\n");
    
    // Ligne 2 //
    printf("*  ");
    for(int traceX = 0; traceX < taillePlateauX; traceX++){
        
        printf("    ");
        
    }
    printf("*\n");
    
    // Ligne 3 //
    printf("*  ");
    for(int traceX = 0; traceX < taillePlateauX; traceX++){
        
        cpt = cpt + 4;
        
    }
    cpt -= tailleText;
    cptRest = (cpt % 2) + (cpt / 2);
    cpt /= 2;
    for(int traceX = 0; traceX < cpt; traceX++){
        
        printf(" ");
        
    }
    printf("%s", text);
    for(int traceX = 0; traceX < cptRest; traceX++){
        
        printf(" ");
        
    }
    printf("*\n");
    
    // Ligne 4 //
    printf("*  ");
    for(int traceX = 0; traceX < taillePlateauX; traceX++){
        
        printf("    ");
        
    }
    printf("*\n");
    
    // Ligne 5 //
    printf("***");
    for(int traceX = 0; traceX < taillePlateauX; traceX++){
        
        printf("****");
        
    }
    printf("*\n\n");
    
    
    
}

/**
 Demande à l'utilisateur de saisir une chaîne de caractère

 @param chaine chaîne dans laquel saisir
 @param longueur taille maximum de la saisie
 @return 0 si la saisie est effectuée
 @return -1 en cas d'erreur
 */
int get_string(char * chaine, int longueur) {
    
    char *positionEntree = NULL;
    
    empty_buffer();
    
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            empty_buffer();
        }
        return 0;
    }
    else
    {
        empty_buffer();
        return -1;
    }
    
}


/**
 Demande au joueur de rentrer les coordonnées de cases et affiche le sous-menu de la partie si demandé

 @param plateau plateau du jeu
 @param play paramètres de la partie
 @param onX si =1 demande la saisie de la source
 @return 0 si aucune action du sous-menu n'est requise
 @return -1 si le joueur a sauvegardé la partie
 @return -2 si le joueur veut quitter la partie en cours
 */
int get_coord(int * plateau, gameSettings * play, int onX) {
    
    int subMenu_statut = 0;
    
    int colorActive = COLOR_ACTIVE;
    
    int inputSrcY = 0;
    int inputSrcX = 0;
    int inputDestY = 0;
    int inputDestX = 0;
    
    if(onX == 1) {
        //Saisie du point de départ si demandé
        
        printf("\nQuel pion veux-tu jouer ?\n");
        if(colorActive == 1) {
            print_color("X : ", "yellow", "black");
        }
        else {
            printf("X : ");
        }
        scanf("%2d", &inputSrcX);
        empty_buffer();
        
        if(inputSrcX != 0 && inputSrcX > 0) {
            
            play->movePawn.src.x = inputSrcX-1;
            
            if(colorActive == 1) {
                print_color("Y : ", "yellow", "black");
            }
            else {
                printf("Y : ");
            }
            scanf("%2d", &inputSrcY);
            empty_buffer();
            
            if(inputSrcY != 0 && inputSrcX > 0) {
                
                play->movePawn.src.y = inputSrcY-1;
                
            }
            else if(inputSrcY == 0) {
                
                subMenu_statut = sub_menu((int *)plateau, *play);
                
            }
            
        }
        else if(inputSrcX == 0) {
            
            subMenu_statut = sub_menu((int *)plateau, *play);
            
        }
        
    }
    
    
    // Saisie du point d'arrivé
    if(subMenu_statut >= 0) {
        
        printf("\nOù veux-tu l'emmener ?\n");
        if(colorActive == 1) {
            print_color("X : ", "yellow", "black");
        }
        else {
            printf("X : ");
        }
        scanf("%2d", &inputDestX);
        empty_buffer();
        
        if(inputDestX != 0 && inputDestX > 0) {
            
            play->movePawn.dest.x = inputDestX-1;
            
            if(colorActive == 1) {
                print_color("Y : ", "yellow", "black");
            }
            else {
                printf("Y : ");
            }
            scanf("%2d", &inputDestY);
            empty_buffer();
            
            if(inputDestY != 0 && inputDestY > 0) {
                
                play->movePawn.dest.y = inputDestY-1;
                
            }
            else if(inputDestY == 0) {
                
                subMenu_statut = sub_menu((int *)plateau, *play);
                
            }
            
        }
        else if(inputDestX == 0) {
            
            subMenu_statut = sub_menu((int *)plateau, *play);
            
        }
        
    }
    
    return subMenu_statut;
    
}

