#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//solitamente è il numero massimo di argomenti passabili a uno script C
//se si fa la stessa cosa per la variabile "env" allora meglio usare 4096
#define MAX_ARGC 128

//Funzione di supporto per visualizzazione esempio
void scriviByteGrezzi(const char *path) {
    int fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd_out == -1) {
        perror("Errore inizializzazione file");
        exit(EXIT_FAILURE);
    }

    unsigned char dati_grezzi[] = {
        'L', 'o', 'r', 'e', 'm', '\0', 
        'I', 'p', 's', 'u', 'm', '\0', 
        'd', 'o', 'l', 'o', 'r', '\0', 
        's', 'i', 't', '\0'
    };

    write(fd_out, dati_grezzi, sizeof(dati_grezzi));
    close(fd_out);
}

int main(int argc, char *argv[]){
    scriviByteGrezzi(argv[1]);

    //<-- INIIO CODICE UTILE
    int fd = open(argv[1], O_RDONLY);
    char buf[64];
    ssize_t bytesR = read(fd, buf, sizeof(buf));

    char *vector[MAX_ARGC];
    int elem = 0;
    char *ptr = buf;

    while(ptr < buf + bytesR && elem < MAX_ARGC - 1){
        vector[elem++] = ptr;
        ptr += strlen(ptr) + 1;
    }
    vector[elem] = NULL;

    close(fd);
    //--> FINE CODICE UTILE

    //Stampe per visualizzazione
    for (int i = 0; i < elem; i++) {
        printf("vector[%d]: %s\n", i, vector[i]);
    }
}

//Quando si leggono byte grezzi, come da STDIN_FILENO
//e si ha una cosa del tipo:
// LOREM\0IPSUM\0DOLOR\0SIT\0AMET\0
// e si vuole salvare questa serie di stringhe, scritta in un buffer, allora il codice 
// scritto e' ideale, e si ottine una cosa del tipo:
// 
// vector[0] -> LOREM
// vector[1] -> IPSUM
// vector[2] -> DOLOR 
// ....