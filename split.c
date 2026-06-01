#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// preso in input una stringa di lunghezza arbitraria
// suddivididiamo quella stringa in a chunk di 8 byte
// e mettiamo le porzioni in un buffer
// stampiamo ogni volta quel buffer
int main(int argc, char *argv[]){

    // estrapoliamo la lunghezza della stringa e posizioniamola nel buffer di input
    const int length = strlen(argv[1]); 
	char input[length+1];
	strcpy(input, argv[1]);

    // preso adesso un buffer di esattamente 8 byte + 1 terminatore
    char buf[9];
    memset(buf, 0, sizeof(buf));
	int i = 0;

    // finche' non si trova il terminatore di stringa
    while (input[i] != '\0'){
        // questi sono i caratteri che devono essere ancora letti
        int remainingChars = length - i;
        int numBytes = 0;
        // se ci sono più di 8 caratteri, allora la dimensione massima e' 8
        // altrimenti il numero di caratteri rimasti
        if(remainingChars >= 8){numBytes = 8;} else {numBytes = remainingChars;}

        // azzeriamo il buffer per sicurezza
        memset(buf, 0, 8);
        // lo riempiamo usando ALGEBRA DEI PUNTATORI
        memcpy(buf, input + i, numBytes);

        // ci spostiamo in avanti di esattamente il numero di byteLetti
        i += numBytes;

        // METODO UTILISSIMO PER INVIARE *UNA* STRINGA
        // DI LUNGHEZZA ARBITRARIA CON SEGNALI
        // IN QUEL CASO PRESTARE ATTENZIONE A **char buf[9]**
        printf("%s\n", buf);
    }
    
}