//
//  general-function.c
//  Halma_xcode [v1.0]
//
//  Created by Romain Bourré on 27/12/2016.
//  Copyright © 2016 Romain Bourré. All rights reserved.
//


#include <time.h>
#include <string.h>

#include "structures.h"

#include "general-function.h"



/**
 Décompose un nombre entier en somme d'entiers consécutifs partant de 1.
 
 @param entier nombre entier à décomposer
 @return renvoie le dernier entier de la somme
 */
int int_compose(int entier) {
    
    int somme = 0;
    int cpt = 0;
    
    while(somme < entier) {
        
        cpt++;
        
        somme = somme + cpt;
        
    }
    
    return cpt;
    
}



/**
 Met en pause le programme.

 @param nbrSec temps de pause en seconde.
 */
void sleep_prog(int nbrSec) {
    
    clock_t befTime;
    clock_t aftTime;
    clock_t diff = 0;
    
    int_compose(2);
    
    befTime = clock();
    
    do {
        
        aftTime = clock();
        diff = (aftTime - befTime) / CLOCKS_PER_SEC;
        
    } while( diff < nbrSec );
    
}



/**
 Vide le buffer
 */
void empty_buffer() {


    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}



/**
 Vide une chaîne de caractère.
 
 @param string chaîne de caractère
 @param sizeString taille de la chaîne de caractère
 */
void init_string(char * string, int sizeString) {
    
    for(int i = 0; i < sizeString; i++) {
        
        string[i] = '\0';
        
    }
    
}


