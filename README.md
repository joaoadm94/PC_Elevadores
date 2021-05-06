# Programacao Concorrente - Projeto 1

### Objetivo

O presente projeto tem como objetivo o desenvolvimento de algoritmos para tratar problemas de comunicação entre processos através de uma memória compartilhada.

### Proposta: modelagem de um sistema de elevadores de um prédio

Considere um edificio de X andares e Y apartamentos por andar.

O edifício conta com dois elevadores: um para uso social e outro para uso de serviço.

#### Uso normal do elevador

Os moradores do edifício podem usar qualquer elevador. 

Cada elevador tem espaço para quatro pessoas.

Após um certo número de usos, o elevador deve ser limpo pelo zelador, e para isso o elevador deve ficar bloqueado no térreo.

No caso de vários zeladores, eles não podem limpar todos os elevadores ao mesmo tempo. Uma certa quantidade de elevadores deve ficar ativa para não prejudicar o fluxo de pessoas.

#### Uso em contexto de pandemia

Devido às restrições do coronavírus, há novas regras para os elevadores.

Um morador só pode entrar no elevador se ele estiver: 1) vazio ou 2) ocupado por pessoas do mesmo apartamento.

### Ciclo de vida de um morador

O morador passa boa parte do seu tempo em casa, mas as vezes precisa sair.

Para sair, ele deve chamar o elevador.

Para o morador embarcar, o elevador deve:
 * parar no andar do morador e
 * ter espaço disponivel e
 * estar indo para o mesmo sentido

Ao embarcar, o morador aguarda até o elevador chegar ao andar desejado.

O morador desce e realiza suas atividades. 

Eventualmente, ele precisa voltar para casa. 

Para voltar, ele deve chamar o elevador.

As regras para o embarque se aplicam aqui novamente.

Quando o morador chega em casa, ele fica até precisar sair novamente.

Quando o morador usa o elevador, ele pode perceber que o mesmo está sujo. Nesse caso, ele aperta o botão de manutenção, avisando ao zelador que o elevador precisa de limpeza.

### Ciclo de vida do zelador

O zelador realiza diversas atividades no edifício. A limpeza do elevador é uma entre elas.

Quando o zelador percebe o sinal de manutenção do elevador, ele deve chamá-lo para limpeza no térreo.

O zelador iniciará a limpeza quando o elevador chegar vazio ao térreo. 
