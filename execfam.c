#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    // === EXECV ===
    // V = Vector
    char *args[] = {"/bin/ls", "-l", ".", NULL};
    execv(args[0], args);
    //unreachable

    // === EXECVE ===
    // V = Vector; E = Environment (ambiente di esecuzione personalizzato)
    char *args[] = {"/bin/ls", "-l", NULL};
    char *env[] = {"USER=gabriele", "HOME=/home/gabriele", NULL};
    execve(args[0], args, env);
    //unreachable

    // === EXECVP ===
    // V = Vector; P = Path
    char *args[] = {"/ls", "-l", NULL};
    exevp(args[0], args); 
    // Molto più comoda di execv, non c'e' bisogno di indicare il PATH
    // lo trova in automatico

    // === EXECVPE ===
    // V = Vector; P = Path; E = Environment
    char *args[] = {"ls", "-l", NULL};
    char *env[] = {"USER=gabriele", "HOME=/home/gabriele", NULL};
    execvpe(args[0], args, env);
    //unreachable

}

// ci sono diversi "exec" possibili
// Sono simili, ma diversi