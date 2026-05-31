#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[]){
    char curdir[PATH_MAX];
    getcwd(curdir, sizeof(curdir));
    
    char ftruepath[PATH_MAX];
    realpath(argv[1], ftruepath);

    struct stat sbf;
    if(stat(argv[1], &sbf) == -1){
        printf("Errore in stat\n");
    }

    if(sbf.st_nlink == 1){
        printf("Il file %s non ha HARDLINKS", argv[1]);
    }

    DIR *dir;
    if((dir = opendir(curdir)) == NULL){
        printf("Errore apertura dir\n");
    }

    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0){
            continue;
        }
        char filepath[PATH_MAX];
        snprintf(filepath, sizeof(filepath), "%s/%s", curdir, entry->d_name);

        if(strstr(ftruepath, filepath) != NULL){
            continue;
        }

        if(entry->d_type == DT_REG){
            struct stat sbcur;   
            if (stat(filepath, &sbcur) == -1){
                printf("Errore in stat(2)\n");
                continue;
            }

            if(sbf.st_dev == sbcur.st_dev && sbf.st_ino == sbcur.st_ino){
                printf("Il file %s è un HARDLINK di %s\n", filepath, argv[1]);
            }


        } else if(entry->d_type == DT_LNK){
            char rp[PATH_MAX];
            realpath(filepath, rp);

            if(strcmp(ftruepath, rp) == 0){
                printf("Il file %s è un SYMLINK di %s\n", filepath, argv[1]);
            }
        }
    }
    closedir(dir);
    
}

// dato un file 'f' e una dir 'd'
    // per trovare i symlink del file 'f' bisogna
    // fare lstat sul file -> se S_ISLINK -> realpath -> se realpath e 'f' coincidono => symlink

    // per trovare gli hardlink del file 'f' bisogna
    // fare stat su 'f' -> se st_nlink > 1 => ha dei link fisici -> su ogni file regolare incontrato
    // faccio stat -> se st_dev di 'f' == st_dev del file && st_ino di 'f' == st_ino del file && 'f' != file scansionato
    // siamo di fronte a un symlink