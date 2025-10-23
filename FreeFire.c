#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Item;

void cadastrarItens(Item itens[], int *n) {
    printf("Quantos itens deseja cadastrar (max %d)? ", MAX);
    scanf("%d", n);
    getchar(); 

    if (*n > MAX) *n = MAX;

    for (int i = 0; i < *n; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Nome: ");
        fgets(itens[i].nome, 30, stdin);
        itens[i].nome[strcspn(itens[i].nome, "\n")] = '\0';
        printf("Tipo: ");
        fgets(itens[i].tipo, 20, stdin);
        itens[i].tipo[strcspn(itens[i].tipo, "\n")] = '\0';
        printf("Prioridade (1-10): ");
        scanf("%d", &itens[i].prioridade);
        getchar();
    }
}

void mostrarItens(Item itens[], int n) {
    printf("\n--- Itens cadastrados ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | Tipo: %s | Prioridade: %d\n",
               i + 1, itens[i].nome, itens[i].tipo, itens[i].prioridade);
    }
}

void selectionSort(Item itens[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(itens[j].nome, itens[min].nome) < 0)
                min = j;
        }
        if (min != i) {
            Item temp = itens[i];
            itens[i] = itens[min];
            itens[min] = temp;
        }
    }
}

int buscaBinaria(Item itens[], int n, char chave[]) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(itens[meio].nome, chave);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

int main() {
    Item itens[MAX];
    int n;
    char chave[30];

    printf("=== Modo Sobrevivência ===\n");
    cadastrarItens(itens, &n);

    printf("\nItens cadastrados com sucesso!\n");
    mostrarItens(itens, n);

    printf("\nOrdenando itens (Selection Sort)...\n");
    selectionSort(itens, n);
    mostrarItens(itens, n);

    printf("\nDigite o nome do item para buscar: ");
    fgets(chave, 30, stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int pos = buscaBinaria(itens, n, chave);
    if (pos != -1)
        printf("Item encontrado: %s | Tipo: %s | Prioridade: %d\n",
               itens[pos].nome, itens[pos].tipo, itens[pos].prioridade);
    else
        printf("Item não encontrado!\n");

    printf("\nFim do jogo. Sobreviveu à ilha!\n");
    return 0;
}
