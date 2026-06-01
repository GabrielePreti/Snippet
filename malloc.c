// Creazione di una struttura dati dinamica capace di contenere
// le entry di un file system

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]){
    // creiamo una struttura dati: array di char dinamici
    // pathStuct[0] -> pippo.txt
    // pathStruct[1] -> pluto.md

    int spaceCreated = 1;
    int usedCells = 0;
    char **pathStruct = malloc(spaceCreated * sizeof(char *));
    //adesso abbiamo solo un pathStruct[0]

    // dichiariamo che all'interno di pathStruct[0] -> voglio creare un buffer di dimensione PATH_MAX
    pathStruct[usedCells] = malloc(PATH_MAX * sizeof(char));

    // utilizziamo questo spazio appena creato
    char filepath[PATH_MAX];
    snprintf(pathStruct[usedCells], PATH_MAX, "%s", argv[1]);

    // espandiamo lo spazio utilizzabile
    usedCells++; spaceCreated++;

    // ridipensioniamo in base allo spazio utilizzabile definito
    char **tmp = realloc(pathStruct, spaceCreated * sizeof(char *));

    if(tmp == NULL){ // controllo
        printf("Errore Critico\n");
        exit(255);
    }

    // ridimensionamento effettuato
    pathStruct = tmp;

    // QUI POSSIAMO EFFETTUARE TUTTE LE OPERAZIONI POSSIBILI

    // stampa per vedere il file path
    printf("%s\n", pathStruct[0]);

    // Pulizia
    for (int i = 0; i < usedCells; i++) {
        free(pathStruct[i]); // Libera ogni singola stringa inserita
    }
    free(pathStruct); // Libera l'array di puntatori
}