#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;
    int tamanho;
    char **bytes;
} Pacote;

// Protótipos das funções
void garantir_capacidade();
void trocar(Pacote *a, Pacote *b);
void heapify_down(int i);
void heapify_up(int i);
void adicionar_heap(Pacote p);
Pacote extrair_min();
void processar_lote(FILE *saida, int *lastPrinted);

// Variáveis globais do heap
Pacote *heap = NULL;
int heap_size = 0;
int heap_capacity = 0;

// Implementações das funções
void garantir_capacidade() {
    if (heap_size >= heap_capacity) {
        int new_capacity = (heap_capacity == 0) ? 1 : heap_capacity * 2;
        Pacote *new_heap = realloc(heap, new_capacity * sizeof(Pacote));
        if (!new_heap) {
            fprintf(stderr, "Falha ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }
        heap = new_heap;
        heap_capacity = new_capacity;
    }
}

void trocar(Pacote *a, Pacote *b) {
    Pacote temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(int i) {
    while (1) {  // Versão iterativa para evitar estouro de pilha
        int menor = i;
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;

        if (esquerda < heap_size && heap[esquerda].numero < heap[menor].numero)
            menor = esquerda;
        if (direita < heap_size && heap[direita].numero < heap[menor].numero)
            menor = direita;

        if (menor == i) break;

        trocar(&heap[i], &heap[menor]);
        i = menor;
    }
}

void heapify_up(int i) {
    while (i > 0 && heap[(i - 1) / 2].numero > heap[i].numero) {
        trocar(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void adicionar_heap(Pacote p) {
    garantir_capacidade();
    heap[heap_size++] = p;
    heapify_up(heap_size - 1);
}

Pacote extrair_min() {
    Pacote min = heap[0];
    heap[0] = heap[--heap_size];
    heapify_down(0);
    return min;
}

void processar_lote(FILE *saida, int *lastPrinted) {
    char linha[65536] = "|";
    int pos = 1;
    int imprimiu = 0;
    int expected = *lastPrinted + 1;

    while (heap_size > 0 && heap[0].numero == expected) {
        Pacote min_p = extrair_min();
        imprimiu = 1;

        // Adiciona bytes do pacote ao buffer
        for (int j = 0; j < min_p.tamanho; j++) {
            int written = snprintf(linha + pos, sizeof(linha) - pos, "%s", min_p.bytes[j]);
            if (written < 0 || written >= sizeof(linha) - pos) break;
            pos += written;
            if (j < min_p.tamanho - 1) {
                written = snprintf(linha + pos, sizeof(linha) - pos, ",");
                if (written >= 0 && written < sizeof(linha) - pos) pos += written;
            }
        }

        // Adiciona "|" e verifica buffer
        int written = snprintf(linha + pos, sizeof(linha) - pos, "|");
        if (written >= 0 && written < sizeof(linha) - pos) pos += written;

        *lastPrinted = min_p.numero;
        expected = *lastPrinted + 1;
    }

    if (imprimiu) {
        // Adiciona quebra de linha após o último "|"
        if (pos < sizeof(linha) - 1) {
            linha[pos] = '\n';
            linha[pos + 1] = '\0';
        } else {
            linha[sizeof(linha) - 2] = '\n';
            linha[sizeof(linha) - 1] = '\0';
        }
        fprintf(saida, "%s", linha);
    }
}

int main(int argc, char* argv[]) {
    FILE *entrada = fopen("entrada.txt", "r");
    FILE *saida = fopen("saida.txt", "w");

    if (!entrada || !saida) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    int n, k;
    fscanf(entrada, "%d %d", &n, &k);

    int lastPrinted = -1;
    int contador = 0;

    for (int i = 0; i < n; i++) {
        Pacote p;
        fscanf(entrada, "%d %d", &p.numero, &p.tamanho);
        p.bytes = malloc(p.tamanho * sizeof(char *));
        if (!p.bytes) {
            fprintf(stderr, "Falha ao alocar memória para bytes.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < p.tamanho; j++) {
            p.bytes[j] = malloc(3 * sizeof(char));
            if (!p.bytes[j]) {
                fprintf(stderr, "Falha ao alocar memória para byte.\n");
                exit(EXIT_FAILURE);
            }
            fscanf(entrada, "%2s", p.bytes[j]);  // Limita leitura a 2 caracteres
        }
        adicionar_heap(p);
        contador++;

        if (contador == k) {
            contador = 0;
            processar_lote(saida, &lastPrinted);
        }
    }

    if (contador > 0) processar_lote(saida, &lastPrinted);

    while (heap_size > 0) {
        processar_lote(saida, &lastPrinted);
    }

    // Liberação de memória
    for (int i = 0; i < heap_size; i++) { 
        for (int j = 0; j < heap[i].tamanho; j++) {
            free(heap[i].bytes[j]);
        }
        free(heap[i].bytes);
    }
    free(heap);

    fclose(entrada);
    fclose(saida);
    return 0;
}