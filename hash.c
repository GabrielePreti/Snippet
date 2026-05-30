//to compile -lssl -lcrypto
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ssl.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 8192

void trovaHash(char *filePath){
    int fd_in = open(filePath, O_RDONLY);
    if(fd_in == -1){
        printf("Errore\n");
        exit(EXIT_FAILURE);
    }

    SHA_CTX shaContenxt;
    SHA1_Init(&shaContenxt);

    unsigned char buf[8192];
    ssize_t bytesRead;
    while((bytesRead = read(fd_in, buf, sizeof(buf))) > 0){
        SHA1_Update(&shaContenxt, buf, bytesRead);
    }

    unsigned char result[SHA_DIGEST_LENGTH];
    SHA1_Final(result, &shaContenxt);

    close(fd_in);

    char hexResult[SHA_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++){
        sprintf(&hexResult[i * 2], "%02x", result[i]);
    }
    hexResult[SHA_DIGEST_LENGTH * 2] = '\0';
    printf("%s\n", hexResult);

    return;
}

int main(int argc, char *argv[]){
    if(argc !=2){
        printf("Errore\n");
        exit(EXIT_FAILURE);
    }
    trovaHash(argv[1]);
    return 0;
}