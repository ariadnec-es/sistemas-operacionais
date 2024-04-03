### ex8_shared_memory.c

      #include <stdio.h>
      #include <sys/types.h>
      #include <sys/wait.h>
      #include <sys/shm.h>
      #include <stdlib.h>
      #include <unistd.h>
      
      int a = 0;
      
      void implementacao_filho1(int *a){
          *a = *a + 1;
          printf("executando filho 1 = %d\n", getpid());
      }
      
      void implementacao_filho2(int *a){
          *a = *a + 2;
          printf("executando filho 2 = %d\n", getpid());
      }
      
      int main(){
          int filho1, filho2, ped, status;
          char *mem;
      
          // Criação de um segmento de memória compartilhada
          int seg_id = shmget(IPC_PRIVATE, 20*sizeof(char), IPC_CREAT | 0666);
      
          printf("Pai comecou (PID=%d)\n", getpid());
      
          // Criação do primeiro processo filho
          filho1 = fork();
          if(filho1 == 0){ //Se for o filho...
              implementacao_filho1(&a); // Chamada da função do filho 1
      
              // Associando o segmento de memória compartilhada ao processo filho
              mem = shmat(seg_id, NULL, 0);
      
              // Escrevendo no segmento de memória compartilhada
              sprintf(mem, "escrevendo teste");
              printf("%s no processo PID=%d\n", mem, getpid());
      
              // Desassociando o segmento de memória compartilhada do processo filho
              shmdt(mem);
              exit(0); // Saindo do processo filho
          }
      
          // Esperando o primeiro filho terminar
          status = wait(NULL);
      
          // Se o primeiro filho terminou com sucesso, cria o segundo filho
          if(filho1 > 0){
              filho2 = fork();
              if(!filho2){ // Se for o filho 2...
                  implementacao_filho2(&a);
                  mem = shmat(seg_id, NULL, 0);
                  printf("%s no processo PID=%d\n", mem, getpid());
                  shmdt(mem);
                  exit(0);
              }
          }
      
          // Esperando o segundo filho terminar
          status = wait(NULL);
      
          // Imprimindo a mensagem de finalização do processo pai e o valor final de 'a'
          printf("(PID=%d) Processo sendo finalizado \n", getpid());
          printf("valor final de a=%d\n", a);
      
          // Removendo o segmento de memória compartilhada
          shmctl(seg_id, IPC_RMID, NULL);
          
          // Saindo do processo pai
          exit(0); 

          // Esta linha nunca será alcançada
          printf("Pai terminou\n");
      
          return 0;
      }


**Aqui está um resumo do que o programa está fazendo:**

O código cria dois processos filhos que compartilham uma variável global a e um segmento de memória compartilhada. Cada filho modifica a de forma diferente e escreve em um segmento de memória compartilhada. O pai espera os filhos terminarem, exibe o valor final de a, remove o segmento de memória compartilhada e finaliza.


### ex8_shared_memory_2.c

      #include <stdio.h>
      #include <sys/types.h>
      #include <sys/wait.h>
      #include <sys/shm.h>
      #include <sys/ipc.h>
      #include <stdlib.h>
      #include <unistd.h>
      
      void implementacao_filho1(int *a){
          *a = *a + 1;
          printf("executando filho 1 = %d\n", getpid());
      }
      
      void implementacao_filho2(int *a){
          *a = *a + 2;
          printf("executando filho 2 = %d\n", getpid());
      }
      
      int main(){
          int filho1, filho2, ped, status;
          char *mem;
          int valor = shmget(IPC_PRIVATE, 20*sizeof(char), IPC_CREAT | 0666);
      
          mem = shmat(valor, NULL, 0);
          if(mem < 0){
                printf("Erro na alocação\n");
                return 0;
           
           }
           *mem = 5;
           printf("Pai comecou (PID=%d) e o valor do inteiro é %d\n", getpid(), *mem);
           filho1 = fork();
           if(filho1 > 0) filho2 = fork();
           if(filho1 == 0){ //Se for o filho1...                    
                 mem = shmat(valor, NULL, 0);
                 
                 sleep(1); // COMENTAR DEPOIS PARA TESTE
                 
                 implementacao_filho1(mem);
                 printf("Filho 1 finalizou (PID=%d) e o valor do inteiro é %d\n", getpid(), *mem);
                 shmdt(mem);
                 exit(0);
            }
            else if(filho2 == 0){ //Se for filho1...
                  mem = shmat(valor, NULL, 0);
                  implementacao_filho2(mem);
                  printf("Filho 2 finalizou (PID=%d) e ovalor de inteiro é: %d\n", mem, getpid(), *mem);
                  shmdt(mem);
                  exit(0);
            }
            for(i = 0; i < 2; i++) wait(NULL);

            shmctl(valor, IPC_RMID, NULL);
            printf("valor=%d\n", *mem);
            printf("Pai terminou\n");
            exit(0);

            return 0;
      }

**Aqui está um resumo do que o programa está fazendo:**

INFORMAÇÕES

### ex11_fork_pipes.c

      #include <stdio.h>
      #include <sys/wait.h>
      #include <stdlib.h>
      #include <unistd.h>
      #include <string.h>

      int main(int argc, char * argv[]){
            int vetor_pipe[2], TAM; // 0 para ler e 1 para escrever; apenas uma convencao...
            pid_t pid;
            TAM = strlen(arg[1]) + 1;
            char buffer[TAM];

            pipe(vetor_pipe); //cria o pipe
            pid = fork(); // cria um novo processo
            if(pid == 0){ // se é o processo filho
                  close(vetor_pipe[1]); // fecha o caminho de escrita pois não será utilizado pelo
                  while (read(vetor_pipe[0], &buffer, TAM) > 0) // Leia enquanto não for o fim(EOF)
                  close(vetor_pipe[0]); // Fecha o caminho de leitura do pipe
                  printf("FILHO: O filho terminou e leu: %s\n", buffer);
                  exit(EXIT_SUCESS);
            }
            else{ //se for o processo-pai
            close(vetor_pipe[0]); // Fecha o caminho de leitura pois não será utilizado
            sleep(2);
            weite(vetor_pipe[1], argv[1], strlen(argv[1])+1); // Envia o conteúdo do parametro
            close(vetor_pipe[1]); // Fecha o caminho de escrita caracterizando o fim(EOF)
            printf("PAI: O pai terminou e escreveu: %s\n", argv[1]);
            wait(NULL); // Espera até que o filho termine
            printf("PAI: O filho terminou\n");
            exit(EXIT_SUCCESS);
            }
         return 0;
      }

**Aqui está um resumo do que o programa está fazendo:**

INFORMAÇÕES

### ex11_fork_pipes2.c

      #include <stdio.h>
      #include <sys/wait.h>
      #include <stdlib.h>
      #include <unistd.h>
      #include <string.h>
      #define MAX_SIZE 4

      int main(int argc, char * argv[]){
            int vetor_pipe_ida[2], vetor_pipe_volta[2];
            pid_t pid;
            char buffer[MAX_SIZE];
            int num, resposta;

            pipe(vetor_pipe_ida); // cria pipe
            pipe(vetor_pipe_volta); // cria pipe
            pid = fork(); // cria um novo processo
            if (pid == 0){ // Se é o processo-filho
                  close(vetor_pipe_ida[1]); // fecha o caminho de escrita E PIPE pois não será
                  while (read(vetor_pipe_ida[0], buffer, MAX_SIZE > 0)); // leia enquanto não for o...

                  sscanf(buffer, "%d", &num);
                  close(vetor_pipe_ida[0]); // Fecha o caminho de leitura do pipe pois concluiu a leitura
                  printf("FILHO: O filho leu %d\n", num);

                  num = num + 1;
                  sprintf(buffer, "%d", num);

                  // Agora vamos RESPONDER ao pai

                  close(vetor_pipe_volta[0]); //Fecha o caminho de leitura DESTE PIPE pois não será
                  write(vetor_pipe_volta[1], buffer, MAX_SIZE); //Envia o conteúdo do parametro passa...
                  close(vetor_pipe_volta[1]); // Fecha o caminho de escrita caracterizando o fim (EOF)
                  printf("PAI: O pai escreveu: %s\n", buffer);

                  // Agora vamos LER a RESPOSTA do filho

                  close(vetor_pipe_volta[1]); //Fecha o caminho de escrita do pipe concluiu a...
                  while (read(vetor_pipe_volta[0], buffer, MAX_SIZE > 0)); // leia enquanto nao for o fim...
                  close(vetor_pipe_volta[0]); // Fecha o caminho de leitura do pipe pois concluiu a...
                  sscanf(buffer, "%d", &num);
                  printf("PAI: O pai leu: %d\n", num);

                  wait(NULL); // Espera até que o filho termine
                  printf("PAI: O filho terminou\n");
                  printf("PAI: O pai terminou\n");
                  exit(0);
            }

            return 0;
      }




