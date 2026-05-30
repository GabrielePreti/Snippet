//Prototipo
//tx invia un segnale contenente un messaggio di 8 caratteri
//aspetta ACK

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void handler(int sig){
    _exit(0);
}

int main(int argc, char *argv[]){

    //=== CONTROLLI DI UTILIZZO ===
    if(argc < 3){
		printf("[ERRORE - USAGE]: nome_eseguibile [pid] [8 caratteri]\n");
		return 1;
	} else if(strlen(argv[2]) > 8) {
		printf("[ERRORE - USAGE]: nome_eseguibile [pid] [8 caratteri]\n");
		return 1;
	}

    //=== COVERSIONE DA STRINGA A NUMERO INTERO ===
    char *endptr;
    long pid_dest = strtol(argv[1], &endptr, 10);
    if(*endptr != '\0'){
        printf("[ERRORE - USAGE]: Pid inserito non valido\n");
    }

    //=== SALVATAGGIO MESSAGGIO E COSTRUZIONE UNION ===
    char bufmsg[9] = "";
    strcpy(bufmsg, argv[2]);

    union sigval value;
	memcpy(&value.sival_ptr, bufmsg, 8);

    //=== INVIO SEGNALE ===
    if(sigqueue(pid_dest, SIGRTMIN, value) == 0){
		return 0;
	} else{
		fprintf(stderr, "[ERRORE] Errore nell'invio del segnale\n");
		return 1;
	}

    //=== GESTIONE SEGNALE DI ACK ===
    signal(SIGUSR1, handler);

    while(1){
        pause();
    }

    return 0;

}