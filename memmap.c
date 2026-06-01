// mappare file nella memoria virtuale del processo corrente
// considerare un file passato come parametro al processo

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        printf("Errore nell'apertura file\n");
        _exit(255);
    }

    struct stat sb;
    if(lstat(argv[1], &sb) == -1){
        printf("Errore in lstat\n");
        _exit(255);
    }

    if(sb.st_size <= 0){
        close(fd);
        printf("Il file non ha una dimesione sufficiente\n");
        return 1;
    }

    char *fileMap = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(fileMap == MAP_FAILED){
        printf("Errore nella mappatura del file\n");
        close(fd);
        return;
    }

    // MMAP:
    // e' una syscall che mappa un file o un dispositivo direttamente
    // nello spazio di indirizzamento virtuale del processo
    // il processo vede il file come se fosse completamente in RAM

    // Funzioni utili e comode: memmem => analogo di strstr

    munmap(fileMap, sb.st_size);
    close(fd);

}