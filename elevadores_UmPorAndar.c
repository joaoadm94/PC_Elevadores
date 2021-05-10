#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define ANDARES 10 // numero de andares
#define APTOS 2  // numero de apartamentos por andar
#define SOCIAL 1 // numero de elevadores sociais
#define SERVICO 5  // numero de elevadores de servico
#define ZELADOR 1 // numero de funcionarios
#define ELEVADOR 1 
#define MAX_MORADORES 5 // numero maximo de moradores por apto
#define SUBINDO 2
#define DESCENDO 1
#define PARADO 0

int edificio[ANDARES];
int ocupantes;

sem_t elevador;
sem_t subir[ANDARES];
sem_t descer[ANDARES];
sem_t chegar[ANDARES];

struct Morador_args {
  int id;
  int andar;
}

struct Elevador_args {
  int posicao;
  int estado;
}

struct No {
  sem_t* semaforo;
  struct No* proximo;
}

int main(int argc, char *argv[]) {

  int erro;
  int i, n, m;
  int *id;

  pthread_t moradores[ANDARES];
  pthread_t elevador;
  pthread_t zelador;

  // vetor de listas contendo os destinos dos moradores
  struct No * destinos[ANDARES];

  sem_init(&elevador, 0, MAX_MORADORES);

  struct Elevador_args* Elevador = (struct Elevador_args*) malloc(sizeof(struct Elevador_args));
  Elevador->estado = SUBINDO;
  Elevador->posicao = 0; 
  ocupantes = 0;

  pthread_create(&elevador, NULL, &elevador, NULL);

  // Criando as threads de moradores
  // e inicializando os semaforos
  for (i = 0; i < ANDARES; i++) {

    sem_init(&subir[i], 0, 1);
    sem_init(&descer[i], 0, 1);
    sem_init(&chegar_destino[i], 0, 1);

    struct No* sem_morador = (struct No*) malloc(sizeof(struct No));
    sem_morador->semaforo = &chegar_destino[i];
    sem_morador->proximo = NULL;

    edificio[i] = 0;

    struct Morador_args* Morador  = (struct Morador_args*) malloc(sizeof(struct Morador_args));
    Morador->id = i;
    Morador->andar_origem = i;  

    pthread_create(&moradores[i], NULL, morador, (void *) (Morador));
  }


  pthread_join(moradores[0], NULL);
  return 0;

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

void * morador (void* args) {
  int id = args->id;
  int posicao = args->andar_origem;
  int andar_destino;

  while(1)
  {
    // fica em casa até decidir sair
    sleep();

    andar_destino = posicao;

    while (andar_destino == posicao) {

      andar_destino = rand() % ANDARES;

    }

    // se o morador deseja subir, a posicao atual sera menor que o destino 
    // se for descer, a posicao atual sera maior que o destino 
    if (posicao < andar_destino) {
      printf("O morador %d deseja subir para o andar %d\n", id, andar_destino);
      sem_wait(&subir[posicao]);
    } else {
      printf("O morador %d deseja descer para o andar %d\n", id, andar_destino);
      sem_wait(&descer[posicao]);
    }
    // passar desse trecho indica que o elevador parou no andar com o sentido
    // desejado

    // aguardando o elevador
    sem_wait(&elevador);

    // conseguiu entrar no elevador

    // confere a possibilidade de entrar no elevador
        // tem espaço? está indo para o mesmo sentido? 
        // os ocupantes são do mesmo apartamento?
        // (talvez só a questão do espaço seja relevante)
    // espera chegar no andar desejado para sair
    // posicao = 
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
