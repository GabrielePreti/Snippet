//RX riceve un segnale
//invia ACK

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void handler(int sig, siginfo_t *info, void *ucontext){
    // === OTTENIMENTO VALORI DA STAMPARE ===
    char msg[9] = "";
    memcpy(msg, &info->si_value.sival_ptr, 8);

    // === STAMPA ===
    write(STDOUT_FILENO, msg, sizeof(msg));
    write(STDOUT_FILENO, "\n", 1);

    // === INVIO SEGNALE DI ACK ===
    kill(info->si_pid, SIGUSR1);

    exit(0);
}

int main(int argc, char *argv[]){
    pid_t mypid = getpid();
    printf("PID: %d\n", mypid);

    // === COSTRUZIONE STRUTTURA SIGACTION PER RICEZIONE SEGNALE ===
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;

    // === REGISTRAZIONE GESTIONE SEGNALE ===
    sigaction(SIGRTMIN, &sa, NULL);

    while(1){
        pause();
    }

    return 0;
    
}