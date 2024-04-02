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
          exit(0); // Saindo do processo pai
          printf("Pai terminou\n"); // Esta linha nunca será alcançada
      
          return 0;
      }


**Aqui está um resumo do que o programa está fazendo:**

O código cria dois processos filhos que compartilham uma variável global a e um segmento de memória compartilhada. Cada filho modifica a de forma diferente e escreve em um segmento de memória compartilhada. O pai espera os filhos terminarem, exibe o valor final de a, remove o segmento de memória compartilhada e finaliza.



