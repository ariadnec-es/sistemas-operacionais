# Sistemas Operacionais
### IMD0036 - SISTEMAS OPERACIONAIS - Códigos para estudo. 

***Unidade 1 - Introdução, Gerencia de Processos, Threads e Escalonamento.***

  ***Capítulos***

###### _1. Gerencia de Processos - Conceitos_
 ---

###### _2. Gerencia de Processos - Implementação e comunicação_ 
 ---

- [Link - Gerencia de Processos: Implementação](https://youtu.be/srrx0t1NpJo?si=MIUALBocChn291U2)
- [Link - Gerencia de Processos: Comunicação](https://youtu.be/nKId0mYdJzA?si=_DWGJ2A1BmX99rQB)
 
 ##### >>IMPLEMENTAÇÃO 

Processo pai cria processo filho, o qual pode criar outros processos, formando uma árvore de processos. Eles executam concorrentemente, mas o pai espera até o filho terminar.


PID - Indentificador de Processos

Comando para verificação de processos no Linux

| Comandos  | Ações |
| --- | --- |
| *top*  |  Verifica os processos no Linux  |
| *cd ~/Documentos/Sistemas_Operacionais/* | Entra no diretório onde encontra-se os arquivos .c  |
| *fork*    | cria um novo processo |
| *exec*    | É usado após o fork para sobrescrever o espaço de memória do processo com um novo programa |
| *execlp(char * caminho, char * parametros);*| Lista de parâmetros é terminada com NULL |
| *getpid()*   | Retorna o PID do processo |
| *getppid()*   | Retorna o PID do processo-pai |
| *getuid()*   | Retorna o ID do usuário  |
| *getgid()*   | Retorna o ID do grupo  |
| *wait()*   | Retorna o valor do processo-filho finalizado, -1 caso não tenha filhos  |
| *exit()*   | void exit(char n); deve ser passado como parametro um valor entre 0 e 255 que representa uma informação sobre finalização do processo  |



Comandos para execução no Linux ex1

    gcc ex1_fork_simple.c -o ex1_fork_simple
    \.ex1_fork_simple
 [Código - ex1_fork_simple.c](2_GerenciaDeProcessos_Implementação.md#ex1_fork_simplesc)

Comandos para execução no Linux ex2

    gcc ex2_fork_pid_simples.c -o ex2_fork_pid_simples
    \.ex2_fork_pid_simples
 [Código - ex2_fork_pid_simples.c](2_GerenciaDeProcessos_Implementação.md#ex2_fork_pid_simplesc)

Comandos para execução no Linux ex3

    gcc ex3_fork_exec.c -o ex3_fork_exec
    \.ex3_fork_exec
 [Código - ex3_fork_exec.c](2_GerenciaDeProcessos_Implementação.md#ex3_fork_execc)

Comandos para execução no Linux ex4

    gcc ex4_fork_com_retorno.c -o ex4_fork_com_retorno
    \.ex4_fork_com_retorno
 [Código - ex4_fork_com_retorno.c](2_GerenciaDeProcessos_Implementação.md#ex4_fork_com_retornoc)

Comandos para execução no Linux ex4

    gcc ex4_fork_sleep.c -o ex4_fork_sleep
    \.ex4_fork_sleep
 [Código - ex4_fork_sleep.c](2_GerenciaDeProcessos_Implementação.md#ex4_fork_sleepc)

Comandos para execução no Linux ex5

    gcc ex5_fork_multiplo1.c -o ex5_fork_multiplo1
    \.ex5_fork_multiplo1
 [Código - ex5_fork_multiplo1.c](2_GerenciaDeProcessos_Implementação.md#ex5_fork_multiplo_1c)

Comandos para execução no Linux ex5

    gcc ex5_fork_multiplo2.c -o ex5_fork_multiplo2
    \.ex5_fork_multiplo2
 [Código - ex5_fork_multiplo2.c](2_GerenciaDeProcessos_Implementação.md#ex5_fork_multiplo_1c)

 Comandos para execução no Linux exercício

    gcc exercício1.c -o exercício1 
    \.exercício1
 [Código - exercício1.c](caminho/arquivo#L13)

 
 ##### >>COMUNICAÇÃO

 IPC - Comunicação entre Processos
 
 **Podem ser:**

 - Independentes: Não podem afetar ou ser afetados pela execução de outros processos.
 - Cooperantes: Podem afetar ou ser afetados pela execução de outros processos, pois compartilham informações, aumenta a velocidade da computação e melhora a convivência.

*Modelo de comunicação*

![image](https://github.com/ariadnec-es/sistemas-operacionais/assets/84780402/88e4a03f-f4e0-41ab-a7cd-c38e815b5613)

**a)**  Nesse modelo é usado mail-box, caixa de email, o kernel vai todo o processo de comunicação entre os dois processos

**b)** Memória compartilhada: Aqui o Shared var criar um espaço de compartilhamento das informações

1 - Deve ser criado um segmento de memória compartilhada por meio

    int shmget(key_t, int size, int shmflg);
   
**Exemplo:**

     segment id = shmget (IPC PRIVATE, size, IPC_CREAT | 0666);

| Parâmetros | Ações |
| --- | --- |
| *key_t* |  Chave de acesso que identifica o segmento de memória é compartilhado ou privado  |
| *size* | É o tamanho do segmento a ser criado em bytes  |
| *shmflg* | Identifica os direitos de acesso de leitura, escrita e execução |
| *shmid* | O valor retorna um identificador do segmento de memória |

2 - O processo que deseja acesso a memória compartilhada deve se **ANEXAR/ ACOPLAR** a ela:

    void *shmat(int shmid, const void *shmaddr, int shmflg);
    
**Exemplo:**

    shared_memory = (char *) shmat(id, NULL, 0);

| Parâmetros | Ações |
| --- | --- |
| *shmid* | Identifica o segmento de memória que se deseja acoplar. Se o valor for NULL ou 0, a memória compartilhada é anexada ao primeiro endereço possível determinado pelo sistema(Comum acontecer) - Ponteiro para memória compartilhada |
| *shmflg* | Argumento que identifica parâmetros diferentes para o endereçamento, o valor retornado é o endereço do segmento de memória compartilhado. Em caso de erro, o valor retornado é -1 |

3 - Agora o processo pode escrever na memória compartilhada **ESCREVER** na memória e quando terminar, um processo pode desanexar a memória compartilhada do seu espaço de armazenamento.

     sprintf(shared_memory, "teste de mem compartilhada");

Ao terminar, desanexar:

     shmdt(shared_memory);

**Atividade**
Faça um programa que cria dois processos filhos, o programa deve criar um segmento de memória compartilhado que contém um inteiro, que deve ser inicializado com um valor qualquer. Este inteiro deve ser incrementado pelo filho 1 e um seguida multiplicado por 2 pelo filho 2.

    gcc exercício1.c -o exercício1 
    \.exercício1
 [Código - exercício1.c](caminho/arquivo#L13)

 ---
###### _3. Threads_
 ---

###### _4. Threads - Implementação_
---
    
###### _5. Escalonamento - Prática_
---

**Unidade 2 - Aguardando**

  **Capítulos**

_1 - Aguardando..._

_2 - Aguardando..._

_3 - Aguardando..._







