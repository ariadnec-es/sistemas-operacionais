# ex1_fork_simples.c

      #include <sys/types.h>
      #include <sys/wait.h>
      #include <stdio.h>
      #include <unistd.h>
      
      int main(){
      	pid_t pid;
      	pid = fork();
      		if(pid<0){
      			printf("Erro ao criar processo\n");
      			return 1;
      
      		}
      		else if(pid == 0){
      			printf("Esta é a execução do filho\n");
      			for(;;);
      		}
      		else{
      			printf("O pai está esperando o filho\n");
      			for(;;);
      			printf("Processo-Filho finalizou\n");
      		}
      	return 0;
      }

# ex2_fork_pid_simples.c

      #include <sys/types.h>
      #include <sys/wait.h>
      #include <stdio.h>
      #include <unistd.h>
      #include <stdlib.h>
      
      int main(){
      	pid_t pid;
      	pid = fork();
      		if(pid < 0){
      			printf("Erro ao criar processo\n");
      			return 1;
      
      		}
      		else if(pid == 0){
      			printf("Esta é a execução do filho(PID=%d), cujo pai tem PID=%d\n", getpid(), getppid());
      			for(;;);
      		}
      		else{
      			wait(NULL);
      			printf("Processo-Filho finalizou\n");
      		}
      	return 0;
      }

# ex3_fork_exec.c

      #include <sys/types.h>
      #include <sys/wait.h>
      #include <stdio.h>
      #include <unistd.h>
      #include <stdlib.h>
      
      int main(){
      	pid_t pid;
      	pid = fork();
      		if(pid < 0){
      			fprintf(stderr, "Criação Falhou");
      			exit(-1);
      
      		}
      		else if(pid == 0){
      			printf("Esta é a execução do filho(PID=%d), cujo pai tem PID=%d\n       ", getpid(), getppid());
      				execlp("/bin/ls","ls","-l",NULL);
      				printf("testando o execlp \n");
      				exit(0);
      		}
      		else{
      			wait(NULL);
      			printf("Processo-Filho finalizou\n");
      			exit(0);
      		}
      	return 0;
      }

# ex4_fork_com_retorno.c

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

# ex4_fork_sleep.c

      #include <sys/types.h>
      #include <sys/wait.h>
      #include <stdio.h>
      #include <unistd.h>
      
      int main(){
      	pid_t pid;
      	pid = fork();
      		if(pid<0){
      			printf("Erro ao criar processo\n");
      			return 1;
      		}
      		else if(pid == 0){
      			printf("Esta é a execução do Filho\n");
      			printf("Esperando... \n");
      			sleep(10);
      			printf("Voltou!\n");
      			execlp("/bin/ls","ls","-l",NULL);
      		}
      		else{
      			wait(NULL);
      			printf("Processo-Filho finalizou\n");
      		}
      	return 0;
      }

# ex5_fork_multiplo_1.c

      #include <sys/types.h>
      #include <sys/wait.h>
      #include <stdio.h>
      #include <unistd.h>
      #include <stdlib.h>
      
      int a=0;
      void implementacao_filho1(int *a){
      	*a = *a + 1;
      	printf("executando filho 1 = %d\n", getpid());
      }
      
      void implementacao_filho2(int *a){
      	*a = *a + 2;
      	printf("executando filho 2 = %d\n", getpid());
      }
      
      int main (){
      	int filho1, filho2, pid, status;
      	printf("Pai comecou (pid=%d)\n", getpid());
      
      	filho1 = fork();
      	if(!filho1){
      		implementacao_filho1(&a);
      		exit(0);
      	}
      	wait(NULL);
      	if(filho1 > 0){
      		filho2 = fork();
      		if(!filho2){
      			implementacao_filho2(&a);
      			exit(0);
      		}
      	}
      
      	pid = wait(NULL);
      	printf("(PID=%d) O pid do processo finalizado é: %d\n", getpid(),pid);
      	printf("valor final de a = %d\n", a);
      
      	exit(0);
      	printf("Pai Terminou");
      
      	return 0;
      }

# ex5_fork_multiplo_2.c

      #include <sys/types.h>
      #include <sys/wait.h>
      #include <stdio.h>
      #include <unistd.h>
      
      int main (){
      	pid_t pid[5]={-1, -1, -1, -1, -1};
      	int status;
      	pid[0] = fork();
      	if(pid[0]<0){
      		printf("Erro ao criar processo #0\n");
      		return 1;
      	}
      	if(pid[0] > 0){ //Se for o pai...
      		printf("PAI: criando o segundo processo\n");
      		pid[1] = fork();
      
      		if(pid[1]<0){
      			printf("Erro ao criar processo #1\n");
      			return 1;
      		}
      	}
      
      	if(pid[0] == 0){
      		printf("FILHO#0: Criando o processo filho do filho cujo PID é %d\n", getpid());
      		pid[2] = fork();
      	}
      
      	if(pid[1] == 0){
      		printf("FILHO#1: Criando o processo filho do filho #1\n");
      		pid[3] = fork();
      	}
      
      	if((pid[0] == 0) || (pid[1] == 0)){
      		for(;;);
      		//execlp("/bin/ls", "ls", NULL);
      	} else{
      		status = wait(NULL);
      		printf("Proocesso-Filho #%d finalizou\n", status);
      	}
      	return 0;
      }

