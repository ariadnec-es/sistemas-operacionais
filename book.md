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
 [Código - ex1_fork_simple.c](caminho/arquivo#L13)

Comandos para execução no Linux ex2

    gcc ex2_fork_pid_simples.c -o ex2_fork_pid_simples
    \.ex2_fork_pid_simples
 [Código - ex2_fork_pid_simples.c](caminho/arquivo#L13)

Comandos para execução no Linux ex3

    gcc ex3_fork_exec.c -o ex3_fork_exec
    \.ex3_fork_exec
 [Código - ex3_fork_exec.c](caminho/arquivo#L13)

Comandos para execução no Linux ex4

    gcc ex4_fork_com_retorno.c -o ex4_fork_com_retorno
    \.ex4_fork_com_retorno
 [Código - ex4_fork_com_retorno.c](caminho/arquivo#L13)

Comandos para execução no Linux ex4

    gcc ex4_fork_sleep.c -o ex4_fork_sleep
    \.ex4_fork_sleep
 [Código - ex4_fork_sleep.c](caminho/arquivo#L13)

Comandos para execução no Linux ex5

    gcc ex5_fork_multiplo1.c -o ex5_fork_multiplo1
    \.ex5_fork_multiplo1
 [Código - ex5_fork_multiplo1.c](caminho/arquivo#L13)

Comandos para execução no Linux ex5

    gcc ex5_fork_multiplo2.c -o ex5_fork_multiplo2
    \.ex5_fork_multiplo2
 [Código - ex5_fork_multiplo2.c](caminho/arquivo#L13)

 Comandos para execução no Linux exercício

    gcc exercício1.c -o exercício1 
    \.exercício1
 [Código - exercício1.c](caminho/arquivo#L13)

 
 ##### >>COMUNICAÇÃO
 
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







