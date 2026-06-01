#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// si prendono diverse stringhe come paramentro
// si concatenano tutte in una stringa unica
// si fanno i chunk

// esempio: tremendamente politicamente cagionevole spericolato
// chunk[0]: "tremenda"
// chunk[1]: "mente po"
// chunk[2]: "liticame"
// chunk[3]: "nte cagi"
// chunk[4]: "onevole "
// chunk[5]: "spericol"
// chunk[6]: "ato"

int main(int argc, char *argv[]) {
    // il '-1' dipende da quuando iniziano i parametri di stringa
    int numStrings = argc - 1;

    int totalLen = 0;
    // calcolo della lunghezza totale della stringa grande
    for (int s = 0; s < numStrings; s++) {
        totalLen += strlen(argv[s + 1]);
    }
    // aggiungo gli spazi e tolgo lo spazio finale
    totalLen += numStrings - 1;

    // allocazione di un'unica stringa e concatena tutto
    char *big_string = malloc(totalLen + 1);
    big_string[0] = '\0';
    for (int s = 0; s < numStrings; s++) {
        // concatenazione
        strcat(big_string, argv[s + 1]);
        if (s < numStrings - 1) {
            strcat(big_string, " ");  // spazio tra le stringhe, non dopo l'ultima
        }
    }

    // inizio della logica dei chunk
    int numChunks = (totalLen + 7) / 8;
    char **chunks = malloc(numChunks * sizeof(char *));

    int i = 0, chunkIndex = 0;
    while (big_string[i] != '\0') {
        int remainingChars = totalLen - i;
        int numBytes = (remainingChars >= 8) ? 8 : remainingChars;

        chunks[chunkIndex] = malloc(9 * sizeof(char));
        memset(chunks[chunkIndex], 0, 9);
        memcpy(chunks[chunkIndex], big_string + i, numBytes);

        i += numBytes;
        chunkIndex++;
    }

    for (int j = 0; j < numChunks; j++) {
        printf("chunk[%d]: \"%s\"\n", j, chunks[j]);
    }

    // libera
    free(big_string);
    for (int j = 0; j < numChunks; j++) {
        free(chunks[j]);
    }
    free(chunks);
}