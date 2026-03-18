#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define MAX_RESERV 3

 // struct da peca.

typedef struct{
    char tipo;
    int id;
} Peca;
  
  // struct que referencia a fila.
typedef struct {
    Peca itens [MAX];
    int inicio;
    int fim;
    int total;
} Fila;

  // struct que referencia pilha.
typedef struct {
    Peca itens [MAX_RESERV];
    int topo;
} Pilha;

  // funcao para iniciar pilha.
void iniciarPilha(Pilha *p) {
    p->topo = - 1;
}

  // funcao para iniciar a fila.
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

  // vetor que verifica se a pilha esta cheia.
int pilhaCheia (Pilha *p) {
    return p->topo == MAX_RESERV - 1;
}
  
  // vetor que verifica se a fila esta cheia.
int filaCheia (Fila *f) {
    return f->total == MAX;
}

  // vetor que verifica se apilha esta vazia.
int pilhaVazia (Pilha *p) {
    return p->topo == -1;
}

  // vetor que verifica se a fila esta vazia.
int filaVazia (Fila *f) {
    return f->total == 0;
}

  // variavel global que armazena o ID das pecas, ao passar das pecas, a numeracao dos IDs vai send incrementada por (proximoID++) automaticamente.
int proximoID = 0;

  // funcao que gera as pecas.
void gerarPeca(Fila *f) {
    char tipos[] = {'I', 'L', 'K', 'T', 'O', 'M', 'J', 'F'};
    
    for (int i = 0; i < MAX && !filaCheia(f); i++) {
        f->itens[f->fim].tipo = tipos[i];
        f->itens[f->fim].id = proximoID++;
    
        f -> fim = (f->fim + 1) % MAX;
        f -> total++;
    }
}

  // funcao para gerar uma peca por vez. 
void gerarUmaPeca(Fila *f) {
    char tipos[] = {'I', 'L', 'K', 'T', 'O', 'M', 'J', 'F'};
    int tamanho = sizeof(tipos) / sizeof(tipos[0]);

    if (!filaCheia(f)) {
        Peca nova;
        nova.tipo = tipos[rand() % tamanho];
        nova.id = proximoID++;

        inserirPeca(f, &nova);
    }
}

  // funcao de insercao de peca. 
void inserirPeca(Fila *f, Peca *p) {
    if (filaCheia(f)) {
        printf("\nA fila esta cheia, nao e possivel adicionar mais itens.\n");
        return;
    }

    f->itens[f->fim] = *p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

  // funcao de remocao de peca.
void removerPeca (Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("\nA fila esta vazia!\n");
        p->id = -1;
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio +1) % MAX;
    f->total--;

}

  // funcao de guardar peca na pilha (reserva).
void guardarnaReserva (Pilha *p, Peca *pc) {
    if (pilhaCheia(p)) {
        printf("A reserva esta cheia!\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = *pc;
}

  // remover peca da pilha (reserva.)
void removerdaReserva (Pilha *p, Peca *pc) {
    if (pilhaVazia(p)) {
        printf("A reserva esta vazia\n");
        pc->id = -1;
        return;
    }

    *pc = p->itens[p->topo];
    p->topo--;
}

  // funcao que mostra a pilha.
void mostrarPilha (Pilha *p) {
    for (int i = p->topo; i >= 0; i--){
        printf("[%c, %d]", p->itens[i].tipo, p->itens[i].id);
    }

    printf("\n");
}

  // funcao que mostra a fila.
void mostrarFila (Fila *f) { 
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d]", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

  // funcao principal
int main() {

      srand(time (NULL));
      int opcaoPRG;
      Peca remov;
      Fila f;
      Pilha p;
      iniciarPilha(&p);
      inicializarFila(&f);
      gerarPeca(&f);

      do {
      
          printf("\nSistema de Filas do Tetris\n");
          printf("Selecione uma das opcoes a seguir: \n");
          printf("\n================================\n");

          printf("1. Jogar peca.\n");
          printf("2. Reservar peca. \n");
          printf("3. Utilizar peca reservada. \n");
          printf("0. Sair do programa. \n");
          scanf("%d", &opcaoPRG);

          printf("\n================================\n");

          switch (opcaoPRG) {

          case 1:
              removerPeca(&f, &remov);
              if (remov.id != -1) {
                printf("Peca removida : [%c, %d]\n", remov.tipo, remov.id);
            }

           gerarUmaPeca(&f);

            printf("\n");
            printf("\nFila atualizada!\n");
            mostrarFila(&f);
            mostrarPilha(&p);

              break;
    
          case 2:
              if (!pilhaCheia(&p)) {
                  removerPeca(&f, &remov);
                  if (remov.id != -1) {
                      guardarnaReserva(&p, &remov);
                  }
              } else {
                  printf("A reserva ets cheia!\n");
              }

              mostrarFila(&f);
              mostrarPilha(&p);

              break;

          case 3:
             removerdaReserva(&p, &remov);
             if (remov.id != -1) {
             inserirPeca(&f, &remov);
            }

             mostrarFila(&f);
             mostrarPilha(&p);

              break;

          case 0:
              printf("Programa encerrando, ate a proxima! \n");

              break;

          default:
              printf("Opcao invalida!\n");
          }
        
        } while (opcaoPRG != 0);

    return 0;
}
    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha