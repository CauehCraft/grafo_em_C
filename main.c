#include <stdio.h>
#include <stdlib.h>
#define MAX_ARESTAS 200

// Estrutura para representar um nó em uma lista de adjacências
typedef struct no {
    int destino;
    struct no* proximo;
} No;

// Estrutura para representar uma aresta no grafo
typedef struct aresta {
    int origem, destino;
} Aresta;

// Estrutura para representar um grafo
typedef struct grafo {
    int V; // Número de vértices
    No** lista; // Lista de adjacências
} Grafo;

// Função para criar um novo nó na lista de adjacências
No* criarNo(int destino) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->destino = destino;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para criar um grafo com V vértices
Grafo* criarGrafo(int V, Aresta* arestas, int numArestas) {
    int i;
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->V = V;

    // Criando uma matriz da lista de adjacência com tamanho V
    grafo->lista = (No**) malloc(V * sizeof(No*));

    // Inicializando cada lista de adjacência como vazia
    for (i = 0; i < V; ++i)
        grafo->lista[i] = NULL;

    // Adicionando arestas ao grafo
    for(i = 0; i < numArestas; i++) {
        // Adicionando aresta da origem ao destino
        int origem = arestas[i].origem;
        int destino = arestas[i].destino;
        No* novoNo = criarNo(destino);
        novoNo->proximo = grafo->lista[origem];
        grafo->lista[origem] = novoNo;

        // Adicionando aresta do destino à origem
        novoNo = criarNo(origem);
        novoNo->proximo = grafo->lista[destino];
        grafo->lista[destino] = novoNo;
    }

    return grafo;
}



// Função para checar se uma aresta existe no grafo
int checarAresta(Grafo* grafo, int origem, int destino) {
    if (origem < 0 || origem >= grafo->V || destino < 0 || destino >= grafo->V) {
        return 0;
    }
    No* noAtual = grafo->lista[origem];
    while (noAtual) {
        if (noAtual->destino == destino) {
            return 1;
        }
        noAtual = noAtual->proximo;
    }
    return 0;
}



// Função para exibir o grafo
void exibirGrafo(Grafo* grafo) {
    int v, w;
    for (v = 0; v < grafo->V; ++v) {
        //No* noAtual = grafo->lista[v];
        printf("%d: ", v);
        for (w = 1; w < grafo->V; ++w) {
            // checando se existe uma aresta entre v e w e imprimindo 1 caso sim, 0 caso não.
            if (checarAresta(grafo, v, w))
                printf("1 ");
            else
                printf("0 ");
        }
        printf("\n");
    }
}


// Função principal
int main() {
    FILE *file = fopen("output/grafo.txt", "r");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    Aresta arestas[MAX_ARESTAS];
    int V = 0; // Número de vértices no grafo
    int i = 0; // Contador de arestas

    while (!feof(file)) {
        fscanf(file, "%d;%d\n", &arestas[i].origem, &arestas[i].destino);
        if (arestas[i].origem > V)
            V = arestas[i].origem;
        if (arestas[i].destino > V)
            V = arestas[i].destino;
        i++;
    }

    V++; // Ajustando o número de vértices

    fclose(file);

    // criando um grafo a partir das arestas importadas
    Grafo* grafo = criarGrafo(V, arestas, i);

    // exibindo o grafo
    exibirGrafo(grafo);

    return 0;
}