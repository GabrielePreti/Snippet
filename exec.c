#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

// troviamo un eseguibile #!/bin/bash dalla cwd
// se esiste -> lo eseguiamo
// altrimenti ritorniamo

char* findScript(char *dirpath){
    DIR *dir;
    if((dir = opendir(dirpath)) == NULL){
        printf("Errore\n");
        return NULL;
    }

    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0){
            continue;
        }

        static char filePath[PATH_MAX];
        snprintf(filePath, sizeof(filePath), "%s/%s", dirpath, entry->d_name);

        if(entry->d_type != DT_REG){
            continue;
        }

        int fd = open(filePath, O_RDONLY);
        unsigned char buffer[4];
        ssize_t bytesLetti = read(fd, buffer, sizeof(buffer));
        close(fd);

        if(buffer[0] == '#' && buffer[1] == '!'){
            return filePath;
        } else{
            continue;
        }

    }
    closedir(dir);
    return NULL;
}

int main(int argc, char *argv[]){
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        printf("Errore in getcwd\n");
    }

    char *scriptPath = NULL;
    scriptPath = findScript(cwd);
    printf("%s\n", scriptPath);

    if (fork()){
        int status; // una maschera di bit usata dal kernel per scrivere informazioni
        // sulla morte del figlio

        pid_t child; // serve a memorizzare il pid del figlio appena terminato
        child = wait(&status);
        // wexistatus è una macro che permette di estrapolare il numero di uscita del figlio
        // le altre macro molto utilizzate sono in MAN 2 WAIT
        printf("%d terminated(%d)\n", child, WEXITSTATUS(status));
    } else{
        char *args[2];
        args[0] = scriptPath;
        args[1] = NULL;
        execvp(args[0], args);
        // unreachable
    }
}