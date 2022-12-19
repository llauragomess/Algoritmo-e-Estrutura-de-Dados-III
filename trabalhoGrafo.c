#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct No{
    int destino;
    int peso;
    struct No *proximo;
}no;
typedef struct Grafo{
    int quantidade_vertices;
    struct no *lista[MAX];
}grafo;
typedef struct Aresta{
    int origem;
    int destino;
    int peso;
}aresta;

grafo *criar_grafo(aresta arestas[], int quantidade_vertices, int quantidade_arestas);
void imprime_grafo(grafo *p, int quantidade_arestas);
void aresta_adjacente(grafo *p, int quantidade_arestas);
void vertice_adjacente(grafo *p, int quantidade_arestas);
void aresta_incidente(grafo *p, int quantidade_arestas);
void vertice_incidente(grafo *p, int quantidade_arestas);
void vertices_adjacentes(grafo *p, int quantidade_arestas);
void peso_aresta(grafo *p, int quantidade_arestas);
void trocar_vertice(grafo *p, int quantidade_arestas);
void grau_vertice(grafo *p, int quantidade_arestas);
void grauVertice(grafo *p, int quantidade_arestas);


int main(){
    FILE *arquivo;
    int i, cont;
    int quantidade_vertices, quantidade_arestas;
    int op;
    grafo *p;

    aresta *arestas = (aresta*)malloc(sizeof(aresta) * quantidade_vertices);
    arquivo = fopen("grafo.txt", "r");
    fscanf(arquivo, "%d%d", &quantidade_vertices, &quantidade_arestas);
    arestas[quantidade_arestas];

    for(i=0; i<quantidade_arestas; i++){
        fscanf(arquivo, "%d%d%d", &arestas[i].origem , &arestas[i].destino, &arestas[i].peso);
    }
    fclose(arquivo);

    p = criar_grafo(arestas, quantidade_vertices, quantidade_arestas);


    do{
        printf("\n[1]Imprimir o grafo (lista de adjacencia)\n");
        printf("[2]Imprimir arestas adjacentes\n");
        printf("[3]Imprimir vertices adjacentes\n");
        printf("[4]Imprimir as arestas incidentes a um vertice\n");
        printf("[5]Imprimir os vertices incidentes de uma aresta\n");
        printf("[6]Verificar se dois vertices sao adjacentes\n");
        printf("[7]Trocar o peso de uma aresta\n");
        printf("[8]Trocar dois vertices\n");
        printf("[9]Grau saida\n");
        printf("[10]Grau entrada\n");
        printf("[0]Sair\n");
        scanf("%d", &op);



        switch(op){
        case 1:
            imprime_grafo(p, quantidade_arestas);
            break;
        case 2:
            aresta_adjacente(p, quantidade_arestas);
            break;
        case 3:
            vertice_adjacente(p, quantidade_arestas);
            break;
        case 4:
            aresta_incidente(p, quantidade_arestas);
            break;
        case 5:
            vertice_incidente(p, quantidade_arestas);
            break;
        case 6:
            vertices_adjacentes(p, quantidade_arestas);
            break;
        case 7:
            peso_aresta(p, quantidade_arestas);
            break;
        case 8:
            trocar_vertice(p, quantidade_arestas);
            break;
        case 9:
            grau_vertice(p, quantidade_arestas);
            break;
        case 10:
            grauVertice(p, quantidade_arestas);
            break;
        }


    }while(op!=0);


    return 0;

}

grafo *criar_grafo(aresta arestas[], int quantidade_vertices, int quantidade_arestas){
    int i;
    grafo *p = (grafo*)malloc(sizeof(grafo));

    for(i=0; i<quantidade_arestas; ++i){
        p-> lista[i] = NULL;
    }

    for(i=0; i<quantidade_arestas; i++){
        int origem = arestas[i].origem;
        int destino = arestas[i].destino;
        int peso = arestas[i].peso;

        no *novoNo = (no *)malloc(sizeof(no));

        novoNo->destino = destino;
        novoNo->proximo = p->lista[origem];
        p->lista[origem] = novoNo;
        novoNo->peso = peso;
    }

    return p;
}
void imprime_grafo(grafo *p, int quantidade_arestas){
    int i;
    for(i=1; i<quantidade_arestas; i++){
        printf("[%d] ", i);
        no *aux =  p->lista[i];
        while(aux){
            printf("-> %d(%d)", aux->destino, aux->peso);
            aux = aux->proximo;
        }
    printf("\n");
    }
}
void aresta_adjacente(grafo *p, int quantidade_arestas){//aresta adjacente a uma aresta informada pelo usuario
    int i, cont=0;
    aresta busca;
    printf("\nInsira uma aresta: (origem/destino/peso)\n");
    scanf("%d%d%d", &busca.origem, &busca.destino, &busca.peso);

    for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
        while(aux){
            if(aux->destino == busca.destino && busca.origem == i){
                cont++;
            }
            aux = aux->proximo;
        }
    }
    if(cont == 0){
        printf("\nAresta nao encontrada!\n");
    }
    if(cont == 1){
        printf("\nNao possui aresta adjacente!\n");
    }
    else{
        for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
            while(aux){
                if(aux->destino == busca.destino && busca.origem == i){
                    printf("[%d] -> %d(%d)\n", i, aux->destino, aux->peso);
                }
                aux = aux->proximo;
            }
        }
    }
}
void vertice_adjacente(grafo *p, int quantidade_arestas){//v�rtice adjacente a um v�rtice informado pelo usuario
    int i;
    int vertice;
    int cont=0;
    printf("\nInsira um vertice:\n");
    scanf("%d", &vertice);

    for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
        while(aux){
            if(vertice == i){
                printf("[%d] ", aux->destino);
           }else{
                cont++;
            }
        aux = aux->proximo;
        }
    }
    if(cont == quantidade_arestas){
        printf("\nVertice nao encontrado!");
    }
}
void aresta_incidente(grafo *p, int quantidade_arestas){//aresta incidente a um vertice informado pelo usuario
    int i;
    int vertice;
    printf("\nInsira um vertice:\n");
    scanf("%d", &vertice);

    printf("\nArestas incidente:");

    for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
        while(aux){
            if(vertice == i){
                printf("\n[%d] -> %d (%d)", i, aux->destino, aux->peso);
           }
        aux = aux->proximo;
        }
    }
}
void vertice_incidente(grafo *p, int quantidade_arestas){//vertice incidente de uma aresta
    int i;
    aresta busca;
    int peso;
    int op;

    printf("\n[1]Buscar pela aresta");
    printf("\n[2]Buscar pelo peso\n");
    scanf("%d", &op);

    switch(op){
    case 1:
        printf("\nInsira uma aresta: (origem/destino/peso)");
        scanf("%d%d%d", &busca.origem, &busca.destino, &busca.peso);

        for(i=0; i<quantidade_arestas; i++){
            no *aux = p->lista[i];
            while(aux){
                if(busca.origem == i && busca.destino == aux->destino && busca.peso == aux->peso){
                    printf("\nVertice: [%d]\tVertice: [%d]", i, aux->destino);
                }
                aux = aux->proximo;

            }
        }
        break;
    case 2:
        printf("\nInsira o peso da aresta que deseja obter os vertices incidentes: ");
        scanf("%d", &peso);

        for(i=0; i<quantidade_arestas; i++){
            no *aux = p->lista[i];
            while(aux){
                if(peso == aux->peso){
                   printf("\nVertice: [%d]\tVertice: [%d]", i, aux->destino);
                }
                aux = aux->proximo;
            }
        }
        break;
    }
}
void vertices_adjacentes(grafo *p, int quantidade_arestas){
    int i;
    int v1, v2;
    int temp;

    printf("\nInsira um vertice: ");
    scanf("%d", &v1);
    printf("\nInsira um vertice: ");
    scanf("%d", &v2);

    for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
        while(aux){
            if(v1 == i && v2 == aux->destino){
                 temp = 1;
            }else{
            }
            aux = aux->proximo;
        }
    }
    if(temp == 1){
        printf("\nSao adjacentes");
    }else{
        printf("\nNao sao adjacnetes");
    }
}
void peso_aresta(grafo *p, int quantidade_arestas){
    int i;
    aresta busca;
    int peso;
    int troca;
    int temp;

    printf("\nInsira a aresta que deseja trocar o peso:");
    scanf("%d%d%d", &busca.origem, &busca.destino, &busca.peso);

    for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
        while(aux){
            if(busca.origem == i && busca.destino == aux->destino && busca.peso == aux->peso){
                printf("\nInsira o valor do novo peso:");
                scanf("%d", &peso);
                troca = aux->peso;
                aux->peso = peso;
                peso = troca;
                temp = 1;
            }
            aux = aux->proximo;
        }
    }
    if(temp == 1){
        printf("\nPeso trocado. Novo grafo:\n");
        imprime_grafo(p, quantidade_arestas);
    }else{
        printf("\nAresta nao encontrada!");
    }
}
void trocar_vertice(grafo *p, int quantidade_arestas){
    int i;
    int troca;
    int v1, v2;
    int temp;

    printf("Insira um vertice:");
    scanf("%d", &v1);
    printf("Insira um vertice:");
    scanf("%d", &v2);


    for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
        while(aux){
            if(v1 == i || v2 == i++){
                troca = p->lista[v1];
                p->lista[v1] = p->lista[v2];
                p->lista[v2] = troca;
                temp = 1;
            }
            aux = aux->proximo;
        }
    }
    if(temp == 1){
        printf("\nVertices trocados:\n");
        imprime_grafo(p, quantidade_arestas);
    }else{
        printf("Vertices nao encontrados");
    }
}
void grau_vertice(grafo *p, int quantidade_arestas){
    int i;
    int vertice;
    int cont = 0;
    int temp;
    printf("\nInsira um vertice:\n");
    scanf("%d", &vertice);

    for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
        while(aux){
            if(vertice == i){
                cont++;
                temp = 1;
           }
        aux = aux->proximo;
        }
    }

    if(temp != 1){
        printf("\nVertice nao encontrado!\n");
    }else{
        printf("\nO vertice %d, possui grau %d", vertice, cont);
    }
}
void grauVertice(grafo *p, int quantidade_arestas){
    int i;
    int vertice;
    int cont = 0;
    int temp; 
    printf ("\nInsira um vertice: ");
    scanf("%d", &vertice);

    for(i=0; i<quantidade_arestas; i++){
        no *aux = p->lista[i];
        while(aux){
            if(vertice == aux->destino){
                cont++;
                temp = 1;
            }
            aux = aux->proximo;
        }
    }
    if(temp == 1){
        printf("\nO vertice %d, possui grau %d\n", vertice, cont);       
    }else{
        printf("\nVertice nao encontrado");
    }
}
