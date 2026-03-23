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

  // funcao que gera as pecas iniciais.
void gerarPeca(Fila *f) {
    char tipos[] = {'I', 'L', 'K', 'T', 'O'};
    
    for (int i = 0; i < MAX && !filaCheia(f); i++) {
        f->itens[f->fim].tipo = tipos[i];
        f->itens[f->fim].id = proximoID++;
    
        f -> fim = (f->fim + 1) % MAX;
        f -> total++;
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

  // funcao para gerar uma peca por vez, utilizada apos jogar uma peca. 
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
    printf("Pecas em pilha!\n");
    for (int i = p->topo; i >= 0; i--){
        printf("[%c, %d]", p->itens[i].tipo, p->itens[i].id);
    }

    printf("\n");
}

  // funcao que mostra a fila.
void mostrarFila (Fila *f) { 
        printf("Pecas em fila!\n");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d]", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

  // funcao de troca de topo com inicio da fila. 
void trocaInicio(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Verifique se a pilha ou a fila contem pecas!\n");   
        return;
}

    int filaInicio = f->inicio;

    Peca aux = f->itens[filaInicio];
        f->itens[filaInicio] = p->itens[p->topo];
        p->itens[p->topo] = aux;

        printf("As pecas foram trocadas!\n");
}

  // funcao de troca das pecas na pilha com as pecas da fila.
void trocar3(Fila *f, Pilha *p) {
    if (f->total < 3 || p->topo < 2) {
        printf("Nao ha 3 pecas suficientes na fila ou na reserva! \n");
    return;
    }

    for (int i = 0; i < 3; i++){
    
    int idxFila = (f->inicio + i) % MAX;
    int idxPilha = p->topo -i;

    Peca aux = f->itens[idxFila];
         f->itens[idxFila] = p->itens[idxPilha];
         p->itens[idxPilha] = aux;
    }

    printf("As pecas foram trocadas!\n");
}

  //cfuncao para limpar tela.
void limparTela() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
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
          printf("4. Trocar peca atual pela reserva. \n");
          printf("5. Trocar 3 pecas da fila pelas da reserva. \n");
          printf("6. Exibir fila e pilha. \n");
          printf("0. Sair do programa. \n");
          scanf("%d", &opcaoPRG);
          printf("\n================================\n");

          switch (opcaoPRG) {

          case 1:
              limparTela();
              removerPeca(&f, &remov);
              if (remov.id != -1) {
                printf("Peca jogada: [%c, %d]\n", remov.tipo, remov.id);
            }

           gerarUmaPeca(&f);

            printf("\nFila atualizada!\n");
            printf("\n");
            mostrarFila(&f);
            printf("\n");
            mostrarPilha(&p);

              break;
    
          case 2:
              limparTela();
              if (!pilhaCheia(&p)) {
                  removerPeca(&f, &remov);
                  if (remov.id != -1) {
                      guardarnaReserva(&p, &remov);
                      gerarUmaPeca(&f);
                  }
              } else {
                  printf("A reserva esta cheia!\n");
              }

              mostrarFila(&f);
              printf("\n");
              mostrarPilha(&p);

              break;

          case 3:
             limparTela();
             removerdaReserva(&p, &remov);
             if (remov.id != -1) {
               printf("Peca jogada da reserva: [%c, %d]\n", remov.tipo, remov.id);
             }

             printf("\n");
             mostrarFila(&f);
             printf("\n");
             mostrarPilha(&p);

              break;

          case 4:
            limparTela();
            trocaInicio(&f, &p);

            printf("\n");
            mostrarFila(&f);
            printf("\n");
            mostrarPilha(&p);

             break;

          case 5: 
           limparTela();
           trocar3(&f, &p);

           printf("\n");
           mostrarFila(&f);
           printf("\n");
           mostrarPilha(&p);

           break;

          case 6:
          limparTela();
          mostrarFila(&f);
          printf("\n");
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