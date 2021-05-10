#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define ANDARES 10 // numero de andares
#define ELEVADOR 1
#define CAPACIDADE 5 
#define SUBINDO 2
#define DESCENDO 1
#define PARADO 0

void* morador_func (void* args);
void* elevador_func (void* args);
int buscar_chamado_acima();
int buscar_chamado_abaixo();

typedef struct  {
  int id;
  int andar_origem;
} morador_args;

int entrar[ANDARES];
int sair[ANDARES];
int chamados[ANDARES];

sem_t sem_mutex;
sem_t sem_elevador;
sem_t sem_capacidade;
sem_t sem_entrar[ANDARES];
sem_t sem_sair[ANDARES];

int main(int argc, char *argv[]) {

  int i;
  int *id;

  pthread_t moradorid;
  pthread_t elevadorid;

  sem_init(&sem_mutex, 0, 1);

  sem_init(&sem_elevador, 0, 0);

  sem_init(&sem_capacidade, 0, CAPACIDADE);

  pthread_create(&elevadorid, NULL, elevador_func, NULL);

  // Criando as threads de moradores
  // e inicializando os semaforos
  for (i = 0; i < ANDARES; i++) {
    sem_init(&sem_entrar[i], 0, 0);
    sem_init(&sem_sair[i], 0, 0);
    chamados[i] = 0;
    entrar[i] = 0;
    sair[i] = 0;
  }


  morador_args* Morador  = (morador_args*) malloc(sizeof (morador_args));
  Morador->id = 3;
  Morador->andar_origem = 3;

  pthread_create(&moradorid, NULL, morador_func, (void*) Morador);

  pthread_join(moradorid, NULL);
  
  free(Morador);

  return 0;

}

void * morador_func (void* args) {
  morador_args *dados = (morador_args*) args;
  int id = dados->id;
  int posicao = dados->andar_origem;
  int andar_destino;
  int estado;

  printf("Morador %d iniciado! Andar: %d\n", id, posicao);

  while(1)
  {

    // escolhe um andar onde deseja descer.
    // esse codigo garante que o morador nao vai querer ir 
    // para o andar onde ja esta
    andar_destino = posicao;
    while (andar_destino == posicao) {

      andar_destino = rand() % ANDARES;

    }

    sem_wait(&sem_mutex);

    // adiciona um chamado para o andar atual
    entrar[posicao] += 1;
    chamados[posicao] = 1;
    printf("Morador %d chamou o elevador no andar %d\n", id, posicao);
    sleep(1);

    sem_post(&sem_mutex);

    // sinaliza o elevador
    sem_post(&sem_elevador);
    
    // pega um lugar no elevador
    // sem_wait(&sem_capacidade);

    // aguarda o elevador chegar no andar atual
    sem_wait(&sem_entrar[posicao]);
    printf("Morador %d entrou no elevador.\n", id);

    sem_wait(&sem_mutex);

    // apertar botao do andar de destino
    sair[andar_destino] += 1;
    chamados[andar_destino] = 1;
    printf("Morador %d vai ao andar %d.\n", id, andar_destino);

    sem_post(&sem_mutex);

    // sinaliza o elevador para se mover
    sem_post(&sem_elevador);

    // aguarda chegar no andar de destino
    sem_wait(&sem_sair[andar_destino]);

    // libera o lugar no elevador
    //sem_post(&sem_capacidade);

    posicao = andar_destino;

    printf("Morador desceu no andar %d.\n", andar_destino);
    
    srand(time(NULL));
    // fica no andar até decidir sair
    sleep(5);  
  }

  free(dados);
  pthread_exit(0);
  
}

// função que retorna o primeiro andar acima onde o elevador foi chamado
int buscar_chamado_acima(int posicao) {
  int i;
 
  for (i = posicao + 1; i < ANDARES; i++) {
    if (chamados[i] == 1) {
      return i;
    }
  }
  return -1;
}

// função que retorna o primeiro andar abaixo onde o elevador foi chamado
int buscar_chamado_abaixo(int posicao) {
  int i;

  for (i = posicao - 1; i >= 0; i--) {
    if (chamados[i] == 1) {
      return i;
    }
  }
  return -1;
}

// Funcao para calcular o estado do elevador (SUBINDO ou DESCENDO);
// Quando ha chamados acima e abaixo, o estado se mantém;
// Do contrario, o elevador vai na direcao unica dos chamados.
int calcular_estado(int estado, int acima, int abaixo, int atual) {

  if (atual == 1){
    return PARADO;
  }
  //printf("acima - %d     abaixo - %d\n", acima, abaixo);
  if ((acima > -1) && (abaixo > -1)) {
    return estado;
  }
  if (acima > 0) {
    return SUBINDO;
  } 
  if (abaixo > -1) {
    return DESCENDO;
  }
}

void* elevador_func (void* args) {

  int i;
  int valor;
  int estado = PARADO;
  int posicao = 0;
  int acima, abaixo, atual;
  int andar_destino;

  printf("Elevador iniciado!\n");

  while (1) {

    // aguarda chamado para algum andar
    sem_wait(&sem_elevador);

    sem_wait(&sem_mutex);
    atual = chamados[posicao];
    // a função retorna o primeiro andar acima onde há um chamado
    acima = buscar_chamado_acima(posicao);
    // a função retorna o primeiro andar abaixo onde há um chamado
    abaixo = buscar_chamado_abaixo(posicao);
    //printf("acima: %d   abaixo: %d     atual: %d\n", acima, abaixo, atual);
    sem_post(&sem_mutex);

    estado = calcular_estado(estado, acima, abaixo, atual);

    if (estado == PARADO) {
      // permitir todos que querem entrar
      while (entrar[posicao] > 0) {
        sem_post(&sem_entrar[posicao]);
        entrar[posicao]--;
      }

      chamados[posicao] = 0;

    } else {
      printf("Elevador em movimento!\n");

      if (estado == SUBINDO) {
        andar_destino = acima;
        while(posicao < andar_destino) {
          posicao++;
          printf("Elevador está no andar %d\n", posicao);
          sleep(1);
        }
      } else if (estado == DESCENDO) {
        andar_destino = abaixo;
        while (posicao > andar_destino) {
          posicao--;
          printf("Elevador está no andar %d\n", posicao);
          sleep(1);
        }
      }
      
      sem_wait(&sem_mutex);
        
      chamados[posicao] = 0;

      // liberar todos que querem sair
      while (sair[posicao] > 0) {
        sem_post(&sem_sair[posicao]);
        sair[posicao]--;
      }
      // permitir todos que querem entrar
      while (entrar[posicao] > 0) {
        sem_post(&sem_entrar[posicao]);
        entrar[posicao]--;
      }
      
      sem_post(&sem_mutex);
    }


  }
}
