#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // tamanho fixo da fila

// Estrutura que representa uma peça
typedef struct {
    char nome;  // tipo da peça ('I', 'O', 'T', 'L')
    int id;     // identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca elementos[TAM_FILA];
    int frente;  // índice do primeiro elemento
    int tras;    // índice do último elemento
    int quantidade;
} Fila;

// ---------- Funções auxiliares ---------- //

// Inicializa a fila vazia
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->quantidade == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

// Gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];  // seleciona um tipo aleatório
    nova.id = id;
    return nova;
}

// Insere uma nova peça no final da fila (enqueue)
void enfileirar(Fila *fila, Peca novaPeca) {
    if (filaCheia(fila)) {
        printf("\n⚠️  A fila está cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % TAM_FILA;
    fila->elementos[fila->tras] = novaPeca;
    fila->quantidade++;
}

// Remove uma peça da frente da fila (dequeue)
void desenfileirar(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\n⚠️  A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca removida = fila->elementos[fila->frente];
    printf("\n🎮 Peça jogada: [%c %d]\n", removida.nome, removida.id);

    fila->frente = (fila->frente + 1) % TAM_FILA;
    fila->quantidade--;
}

// Exibe o estado atual da fila
void exibirFila(Fila *fila) {
    printf("\n===== Fila de Peças =====\n");
    if (filaVazia(fila)) {
        printf("[vazia]\n");
        return;
    }

    int i, idx;
    for (i = 0; i < fila->quantidade; i++) {
        idx = (fila->frente + i) % TAM_FILA;
        printf("[%c %d] ", fila->elementos[idx].nome, fila->elementos[idx].id);
    }
    printf("\n=========================\n");
}

// ---------- Função principal ---------- //

int main() {
    Fila fila;
    int opcao, contadorIDs = 0;
    srand(time(NULL)); // inicializa gerador aleatório

    inicializarFila(&fila);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(contadorIDs++));
    }

    do {
        exibirFila(&fila);
        printf("\nAções disponíveis:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar(&fila);
                break;
            case 2:
                enfileirar(&fila, gerarPeca(contadorIDs++));
                break;
            case 0:
                printf("\nEncerrando o jogo... 👋\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
