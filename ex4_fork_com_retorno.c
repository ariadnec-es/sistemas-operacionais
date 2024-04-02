#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	int retorno;
	pid = fork();
		if(pid < 0){
			printf("Erro ao criar processo\n");
			return 1;

		}
		else if(pid == 0){
			printf("Esta é a execução do filho(PID=%d), cujo pai tem PID=%d\n       ", getpid(), getppid());
		}
		else{
			retorno = wait(NULL);
			printf("Processo-Filho finalizou e seu PID era: %d\n", retorno);
			exit(0);
		}
	return 0;
}