#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define ANDARES 5 // numero de andares
#define SOCIAL 1 // numero de elevadores sociais
#define SERVICO 5  // numero de elevadores de servico
#define FUNCIS 1 // numero de funcionarios
#define MAX_MORADORES 5 // numero maximo de moradores


void * produtor(void * meuid);
void * consumidor (void * meuid);


void main(argc, argv)
int argc;
char *argv[];
{

  int erro;
  int i, n, m;
  int *id;

  pthread_t tid[PR];
   
  for (i = 0; i < PR; i++)
  {
    id = (int *) malloc(sizeof(int));
    *id = i;
    erro = pthread_create(&tid[i], NULL, produtor, (void *) (id));

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

}

void * produtor (void* pi)
{
 
  while(1)
  {
   

  }
  pthread_exit(0);
  
}

void * consumidor (void* pi)
{
 while(1)
  {
 
  }
  pthread_exit(0);
  
}
