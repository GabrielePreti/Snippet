//system call pipe ha due descritori, pipe[0] è l'estremità di lettura mentre pipe[1] è l'estremità di lettura
//i dati scritti su pipe[1] poppono essere letti da pipe[0]
//è un vero e proprio buffer gestito dal kernel

//struttura: int pipe(int pipefd[2]); : crea un canale di comunicazione

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#define BUFSIZE 1024
uint8_t buf[BUFSIZE];
int main(int argc, char *argv[]){
    int fd[2]; //dichiarazione dell'array del file descriptor, per la syscall pipe
    pipe(fd); //creo il "tubo"
    write(fd[1], "ciao\n", 5); //riempio estremità
    ssize_t n = read(fd[0], buf, BUFSIZE); //leggo estremità
    write(STDOUT_FILENO, buf, n); //stampo risultato NON creando file
    return 0;
}
//(fd[1]) ---> [ BUFFER IN MEMORIA ] ---> (fd[0])
//è utile per la comunicazione tra processi del tipo: fork() + exec()
//è esattamente la pipeline della shell del tipo "ls | wc"
