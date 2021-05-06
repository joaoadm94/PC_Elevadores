#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define ANDARES 3 // numero de andares
#define APTOS 2 // numero de apartamentos por andar
#define SOCIAL 1 // numero de elevadores sociais
#define SERVICO 5  // numero de elevadores de servico
#define ZELADOR 1 // numero de funcionarios
#define MAX_MORADORES 5 // numero maximo de moradores por apto

// matriz que representa a quantidade de moradores por apartamento, e por andar
int moradores[ANDARES][APTOS];

void main(argc, argv)
int argc;
char *argv[];
{

  int erro;
  int i, n, m;
  int *id;
  int conta_moradores = 0;
  int valor;

  srand(time(NULL));

  // populando a matriz de moradores
  for (int j = 0; j < ANDARES; j++) {
    for (int k = 0; k < APTOS; k++) {
      valor = 0;
      while (valor == 0) {
        valor = rand() % MAX_MORADORES;
      }
      moradores[j][k] = valor;
      conta_moradores += valor;
    }
  }

  printf("Total de moradores: %d\n", conta_moradores);

  // criando as threads, cada uma é um morador
  for (int j = 0; j < ANDARES; j++) {
    for (int k = 0; k < APTOS; k++) {
      printf("Apto %d0%d: %d\n", j+1, k+1, moradores[j][k]);
    }
  }



  /*
  pthread_t tid[PR];
   
  for (i = 0; i < PR; i++)
  {
    id = (int *) malloc(sizeof(int));
    *id = i; 
    erro = pthread_create(&tid[i], NULL, morador, (void *) (id));

    if(erro)
    {
      printf("erro na criacao do thread %d\n", i);
      exit(1);
    }
  }

  pthread_t tCid[CN];

  for (i = 0; i < CN; i++)
  {
    id = (int *) malloc(sizeof(int));
    *id = i;
    erro = pthread_create(&tCid[i], NULL, consumidor, (void *) (id));

    if(erro)
    {
      printf("erro na criacao do thread %d\n", i);
      exit(1);
    }
  }
 
  pthread_join(tid[0],NULL);
  */
}

void * morador (void* pi)
{
 
  while(1)
  {
    // fica em casa até decidir sair
    // chama o elevador
    // confere a possibilidade de entrar no elevador
        // tem espaço? está indo para o mesmo sentido? 
        // os ocupantes são do mesmo apartamento?
        // (talvez só a questão do espaço seja relevante)
    // espera chegar no andar desejado para sair
    // se o elevador está sujo, sinaliza ao zelador para realizar a limpeza
  }
  pthread_exit(0);
  
}

void * elevador (void * pi) {
  while (1) {
    // aguarda chamado para algum andar
    // quando recebe o chamado:
      // fecha a porta
      // vai até o andar desejado
      // (precisa armazenar o sentido do elevador para enfileiramento de chamadas?)
  }
}

void * funcionario (void* pi)
{
 while(1)
  {
    // realiza outras tarefas

    // quando o elevador está sujo, prepara para entrar e limpar

    // o elevador fica parado enquanto está sendo limpo
 
  }
  pthread_exit(0);
  
}
